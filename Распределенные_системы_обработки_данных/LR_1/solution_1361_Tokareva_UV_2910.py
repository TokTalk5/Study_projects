from pyspark.sql import DataFrame, Window
from pyspark.sql import functions as F
from common import read_csv


### Работа студентки группы 1361 - Токаревой Ульяны Владимировны


def solve() -> DataFrame:
    match = read_csv('match')
    player = read_csv('player')
    player_result = read_csv('player_result')

    kda = player_result.groupBy('player_id').agg(
        F.floor(F.avg('kill')).alias("avg_kills"),
        F.floor(F.avg('death')).alias("avg_death"),
        F.floor(F.avg('assist')).alias("avg_assists"),
        F.floor(F.avg('gold') / 1000).alias("avg_gold_k")
    )

    winrate = player_result.join(match, "match_id", how="left").groupBy("player_id").agg(
        F.floor(F.avg(F.when(player_result["is_radiant"] == match["radiant_won"], 1).otherwise(0)) * 100).alias("winrate"),
        F.count('player_id').alias("matches_cnt")
    )

    pos_cnt = player_result.groupBy("player_id", "pos").agg(F.count("pos").alias("pos_cnt"))

    player_window = Window.partitionBy("player_id")
    maxpos = pos_cnt.withColumn(
        "max_pos_cnt", F.max("pos_cnt").over(player_window)
    ).filter(
        F.col("max_pos_cnt") == F.col("pos_cnt")
    ).groupBy("player_id").agg(F.min("pos").alias("pos"))

    res = player.join(kda, on="player_id") \
        .join(winrate, on="player_id") \
        .join(maxpos, on="player_id") \
        .select(
        F.row_number().over(Window.partitionBy(F.lit("1")).orderBy(F.desc("matches_cnt"),F.asc("name"))).alias("N"),
        player.name,
        F.col("pos"),
        F.format_string("%d/%d/%d", kda.avg_kills, kda.avg_death, kda.avg_assists).alias("kda"),
        F.format_string("%.0fk", F.col("avg_gold_k").cast("float")).alias("avg_gold"),
        F.format_string("%d%%/%d", F.col("winrate").cast("int"), winrate.matches_cnt).alias("winrate")
    ) \
        .sort("N", ascending=False)

    return res