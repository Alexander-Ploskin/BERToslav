import pandas as pd
from detoxify import Detoxify

from typing import Dict
import numpy as np


def classify(messages, detoxify_model=None):
    # Use the provided detoxify_model or create a new instance if none is provided
    if detoxify_model is None:
        detoxify_model = Detoxify("multilingual")

    res_dict = detoxify_model.predict(messages)
    toxicity_score = np.mean(res_dict["toxicity"])
    return toxicity_score


def get_scores(user_messages: Dict, detoxify_model=None):
    users = user_messages.keys()
    list_scores = list(map(lambda u: classify(user_messages[u], detoxify_model), users))
    user_scores = dict(zip(users, list_scores))
    return user_scores


def process(user_messages: Dict, detoxify_model=None):
    scores = get_scores(user_messages, detoxify_model)
    write_into_file("./output_raw/new.txt", scores)


def write_into_file(file_name, scores):
    with open(file_name, "w") as file:
        for key, value in scores.items():
            file.write(f"{key} {value}\n")
