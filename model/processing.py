import pandas as pd
from detoxify import Detoxify

from typing import Dict
import numpy as np


def classify(messages):
    res_dict = Detoxify("multilingual").predict(messages)
    toxicity_score = np.mean(res_dict["toxicity"])
    return toxicity_score


def get_scores(user_messages: Dict):
    users = user_messages.keys()
    list_scores = list(map(lambda u: classify(user_messages[u]), users))
    user_scores = dict(zip(users, list_scores))
    return user_scores


def process(user_messages: Dict):
    scores = get_scores(user_messages)
    write_into_file("./data/output/new.txt", scores)


def write_into_file(file_name, scores):
    with open(file_name, "w+") as file:
        for key, value in scores.items():
            file.write(f"{key} {value}\n")
