import pandas as pd
from detoxify import Detoxify

from typing import Dict
import numpy as np


def classify(messages):
    res_dict = Detoxify("multilingual").predict(messages)
    toxicity_score = np.mean(res_dict["toxicity"])
    return toxicity_score


def process(user_messages: Dict, top=5):
    users = user_messages.keys()
    list_scores = list(map(lambda u: classify(user_messages[u]), users))
    user_scores = dict(zip(users, list_scores))
    sorted_scores = dict(sorted(user_scores.items(), key=lambda item: item[1]))
    top_toxics = sorted_scores.keys()[:top]
    return top_toxics
