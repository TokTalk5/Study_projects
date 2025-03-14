# Импорт всех необходимых пакетов
from pyspark.sql import DataFrame
from pyspark.sql.functions import col, lit, udf, array_size, array_distinct, explode, count, min, coalesce
from pyspark.sql.types import StringType, ArrayType
from hashlib import md5
from lab2.common import SparkContextCommon

# Константа для деления строк
SUBSTRING_LENGTH = 7

# Удаление пробелов
def clean_data(inp: str) -> str:
    return "".join(inp.split())

# Разбиение на подстроки
def split_str(n: int, data: str) -> list:
    return [data[i:n + i] for i in range(0, len(data) - n + 1)] if n <= len(data) else [data]

# Определение udf
clean_data_udf = udf(clean_data, StringType())
split_bytes_udf = udf(lambda n, data: split_str(n, data), ArrayType(StringType()))
md5_udf = udf (lambda x: md5(x.encode()).hexdigest(), StringType())

# Основная часть
def solve(common: SparkContextCommon) -> DataFrame:

    # Чтение и очистка данных
    raw_df = common.read_data()
    cleaned_df = raw_df.withColumn('content', clean_data_udf(col('content')))

    # Разбиение на подстроки
    substrings_df = cleaned_df.withColumn(
        "substrings", array_distinct(split_bytes_udf(lit(SUBSTRING_LENGTH), col('content')))
    ).withColumn("size", array_size(col("substrings")))

    # Хеширование
    exploded_df = substrings_df.select("author", explode(col("substrings")).alias("substring"))
    hashed_df = exploded_df.withColumn("hash", md5_udf(col("substring")))

    # Сравнение
    comparison_df = hashed_df.alias("lhs").join(
        hashed_df.alias("rhs"),
        (col("lhs.author") != col("rhs.author")) & (col("lhs.hash") == col("rhs.hash")),
        how="inner"
    ).select(
        col("lhs.author").alias("lhs_author"),
        col("rhs.author").alias("rhs_author"),
        col("lhs.hash")
    )

    # Группировка
    grouped_df = comparison_df.groupBy("lhs_author", "rhs_author").agg(count("hash").alias("match_count"))

    # Новый датафрейм с совпадениями
    result_df = grouped_df.join(
        substrings_df.select(col("author").alias("lhs_author"), col("size")),
        on="lhs_author"
    ).select(
        "lhs_author", "rhs_author", (col("match_count") / col("size")).alias("match_percentage")
    )


    # Результат
    common.view("result", result_df)

    # SQL запрос
    return common.spark.sql("""
        SELECT CAST(match_percentage AS Double) AS match,
               CAST(lhs_author AS String) AS lhs_author,
               CAST(rhs_author AS String) AS rhs_author
        FROM result
    """)
