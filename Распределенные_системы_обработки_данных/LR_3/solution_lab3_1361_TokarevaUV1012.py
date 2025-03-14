from pyspark.sql import DataFrame, SparkSession
from pyspark.sql.functions import * 
from pyspark.sql.types import *
from pyspark.shell import spark

# Определяем переменную для названия таблицы CSV-файла
NAME_DATACSV = "RU_youtube_trending_data.csv"  # Название таблицы CSV-файла


def view(name: str, target: DataFrame | str) -> DataFrame:
    """Создает или заменяет временную представительскую таблицу."""
    df = target if isinstance(target, DataFrame) else spark.sql(target)
    df.createOrReplaceTempView(name)
    return df

# Создаем экземпляр SparkSession
spark = SparkSession.builder.appName("MyApp").getOrCreate()

# Указываем путь к CSV-файлу и читаем его в Dataframe
csv_path = "lab3/" + NAME_DATACSV
df = spark.read.csv(csv_path, header=True, inferSchema=True, multiLine=True)
df.createOrReplaceTempView("YT_Data")

# Бинарный признак (надо выбрать 2 признака из группы): 'Популярные теги (#challenge, #asmr)'; 
# Категория: 'Трендовые персоны (Илон Маск, 21 Savage, Магнус Карлсен)'; 
# Коэффициент 'CLR - Процент комментариев от общего числа лайков'

# Определяем схему для категорий видео
schema = StructType([
    StructField("id", IntegerType(), True),
    StructField("name", StringType(), True),
    StructField("template", StringType(), True)
])

# Определяем категории видео
category = [
    (1, "Илон Маск", "%Илон Маск%"),
    (2, "21 Savage", "%21 Savage%"),
    (3, "Магнус Карлсен", "%Магнус Карлсен%")
]

# Создаем DataFrame для категорий видео
categorical_df = spark.createDataFrame(category, schema)
categorical_df.createOrReplaceTempView("category")

# -------------------создание общей статистики ---------------------------------
view("df_total_stat", """
    SELECT 
         date_format(YT_data.trending_date, 'yyyy-MM') AS YM,
         SUM(YT_data.view_count) AS total_view,
         SUM(YT_data.comment_count) AS total_comment,
         SUM(YT_data.likes) AS total_likes,
         ROUND ((SUM(YT_data.comment_count) / SUM(YT_data.likes)), 2) AS total_CLR
    FROM YT_Data AS YT_data
    GROUP BY date_format(YT_data.trending_date, 'yyyy-MM')
""")

# ---------- создание таблицы со всеми категориями с изначальной таблицой ---------------- 
view("df_categoryes", """
    SELECT YT_data.description,YT_data.comment_count,YT_data.likes,YT_data.view_count,YT_data.tags,YT_data.trending_date,YT_data.publishedAt,YT_data.title, 
           c.id AS cat_id, 
           c.name AS cat_name
    FROM YT_Data AS YT_data 
    JOIN category AS c 
    ON YT_data.description ILIKE c.template 
     OR YT_data.title ILIKE c.template 
     OR YT_data.tags ILIKE c.template 
""")

#  -------------- создание статистики для категорий -----------------------
view("df_cats_stat", """
    SELECT 
         date_format(a.trending_date, 'yyyy-MM') AS YM, 
         SUM(a.view_count) AS cats_view,
         SUM(a.comment_count) AS cats_comment,
         SUM(a.likes) AS cats_likes,
         a.cat_id,
         a.cat_name
    FROM df_categoryes AS a
    GROUP BY a.cat_id, a.cat_name, date_format(a.trending_date, 'yyyy-MM')
""")


# --------  сборка таблицы  для категорий ------------
view("df_final_cats_stat", """
    WITH sub AS (
    SELECT t.YM,
         t.total_comment,
         t.total_likes,
         t.total_view,
         t.total_CLR,

         c.cat_name,
         c.cats_view,
         c.cats_comment,
         c.cats_likes,
         ROUND ((c.cats_comment / c.cats_likes), 2) AS cats_CLR
    FROM df_total_stat AS t 
    JOIN df_cats_stat AS c 
    ON t.YM = c.YM
    ORDER BY t.YM DESC, c.cat_id ASC 
    )
    SELECT *, 
         ROUND((total_CLR - cats_CLR), 2) AS diff_CLR_abs,
         CASE 
         	WHEN cats_CLR != 0 
         		THEN ROUND((total_CLR / cats_CLR), 2) 
         		ELSE NULL 
         		END AS diff_CLR_relative
    FROM sub
    WHERE (EXTRACT(MONTH FROM sub.YM) IN (12)
    AND EXTRACT(YEAR FROM sub.YM) IN (2023))
    OR (EXTRACT(MONTH FROM sub.YM) IN (1)
    AND EXTRACT(YEAR FROM sub.YM) IN (2024))
    """)

# Показываем содержимое конечного DataFrame с категориями
spark.sql("SELECT * FROM df_final_cats_stat").show()


# Бинарный признак (надо выбрать 2 признака из группы): 'Популярные теги (#challenge, #asmr)'; 
# ---------- создание таблицы с бинарными признаками с изначальной таблицы -----------------
view("df_bins_challenge", """
        SELECT YT_data.description,YT_data.comment_count,YT_data.likes,YT_data.view_count,YT_data.tags,YT_data.trending_date,YT_data.publishedAt,YT_data.title
    FROM YT_Data AS YT_data
    WHERE (YT_data.description ILIKE '%#challenge%' 
      OR YT_data.tags ILIKE '%challenge%') 
      AND (YT_data.description NOT ILIKE '%#asmr%'
      OR YT_data.tags NOT ILIKE '%asmr%')
      
""")

view("df_bins_asmr", """
        SELECT YT_data.description,YT_data.comment_count,YT_data.likes,YT_data.view_count,YT_data.tags,YT_data.trending_date,YT_data.publishedAt,YT_data.title
    FROM YT_Data AS YT_data
    WHERE (YT_data.description ILIKE '%#asmr%' 
    	OR YT_data.tags ILIKE '%asmr%')
    	AND (YT_data.description NOT ILIKE '%#challenge%' 
        OR YT_data.tags NOT ILIKE '%challenge%')
""")

view("df_bins_chandas", """
        SELECT YT_data.description,YT_data.comment_count,YT_data.likes,YT_data.view_count,YT_data.tags,YT_data.trending_date,YT_data.publishedAt,YT_data.title
    FROM YT_Data AS YT_data
    WHERE (YT_data.description ILIKE '%#challenge%' 
        OR YT_data.tags ILIKE '%challenge%')
    	AND (YT_data.description ILIKE '%#asmr%' 
    	OR YT_data.tags ILIKE '%asmr%')
""")


# ------------ создание статистики для бинарных признаков ---------
view("df_bins_stat_challenge", """
    SELECT SUM(a.likes) AS bins_likes,
         SUM(a.comment_count) AS bins_comment,
         SUM(a.view_count) AS bins_view,
         date_format(a.trending_date, 'yyyy-MM')AS YM
    FROM df_bins_challenge AS a
    GROUP BY date_format(a.trending_date, 'yyyy-MM')
""")

view("df_bins_stat_asmr", """
    SELECT SUM(a.likes) AS bins_likes,
         SUM(a.comment_count) AS bins_comment,
         SUM(a.view_count) AS bins_view,
         date_format(a.trending_date, 'yyyy-MM')AS YM
    FROM df_bins_asmr AS a
    GROUP BY date_format(a.trending_date, 'yyyy-MM')
""")

view("df_bins_stat_chandas", """
    SELECT SUM(a.likes) AS bins_likes,
         SUM(a.comment_count) AS bins_comment,
         SUM(a.view_count) AS bins_view,
         date_format(a.trending_date, 'yyyy-MM')AS YM
    FROM df_bins_chandas AS a
    GROUP BY date_format(a.trending_date, 'yyyy-MM')
""")

# -------------- Сборка статистики для бинарных признаков -------------
view("df_total_bins_stat", """
    SELECT chandas.YM,         
        challenge.bins_likes AS challenge_likes, 
        challenge.bins_comment AS challenge_comment, 
        challenge.bins_view AS challenge_view, 
        
        ROUND ((challenge.bins_comment / challenge.bins_likes ), 2) AS challenge_CLR,
        
        asmr.bins_likes AS asmr_likes, 
        asmr.bins_comment AS asmr_comment, 
        asmr.bins_view AS asmr_view,
        
        ROUND ((asmr.bins_comment / asmr.bins_likes), 2) AS asmr_CLR,
        
        chandas.bins_likes AS chandas_likes, 
        chandas.bins_comment AS chandas_comment, 
        chandas.bins_view AS chandas_view, 
        
        ROUND ((chandas.bins_comment / chandas.bins_likes), 2) AS chandas_CLR
        
    FROM df_bins_stat_chandas AS chandas
    JOIN df_bins_stat_asmr AS asmr ON chandas.YM = asmr.YM
    JOIN df_bins_stat_challenge AS challenge ON chandas.YM = challenge.YM
""")

# -------------- Сборка общей статистики для бинарных признаков -------------
view("df_final_bins_stat", """
WITH sub AS (
    SELECT t.YM,
           t.total_comment,
           t.total_likes,
           t.total_view,
           ROUND ((t.total_comment / t.total_likes), 2) AS total_CLR,
           b.challenge_likes, 
           b.challenge_comment, 
           b.challenge_view,
           b.challenge_CLR,
           b.asmr_likes, 
           b.asmr_comment, 
           b.asmr_view,
           b.asmr_CLR,
           b.chandas_likes, 
           b.chandas_comment, 
           b.chandas_view, 
           b.chandas_CLR
     
    FROM df_total_stat AS t
    JOIN df_total_bins_stat AS b 
     ON t.YM = b.YM
    ORDER BY t.YM DESC)
SELECT *,
       ROUND((total_CLR - challenge_CLR), 2) AS diff_CLR_abs_ch,
       ROUND((total_CLR - asmr_CLR), 2) AS diff_CLR_abs_as,
       ROUND((total_CLR - chandas_CLR), 2) AS diff_CLR_abs_chas,
       ROUND((total_CLR / challenge_CLR), 2) AS diff_CLR_relative_ch,
       ROUND((total_CLR / asmr_CLR), 2) AS diff_CLR_relative_as,
       ROUND((total_CLR / chandas_CLR), 2) AS diff_CLR_relative_chas
FROM sub
    WHERE (EXTRACT(MONTH FROM sub.YM) IN (12)
    AND EXTRACT(YEAR FROM sub.YM) IN (2021))
    OR (EXTRACT(MONTH FROM sub.YM) IN (1)
    AND EXTRACT(YEAR FROM sub.YM) IN (2023))
""")

# Показываем содержимое конечного DataFrame с бинарными признаками
spark.sql("SELECT * FROM df_final_bins_stat").show()

# Завершаем работу с SparkSession
spark.stop()
