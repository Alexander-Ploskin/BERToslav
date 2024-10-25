import pytest
import numpy as np
from processing import (
    classify,
    process,
)


@pytest.fixture
def sample_user_messages():
    return {
        "user1": ["Hello", "How are you?"],
        "user2": ["You're an idiot"],
        "user3": ["I love this!"],
        "user4": ["This is terrible"],
        "user5": ["Have a nice day"],
    }


def test_classify():
    messages = ["Hello", "This is a test", "You are amazing"]
    result = classify(messages)

    assert isinstance(result, float)
    assert 0 <= result <= 1


@pytest.mark.parametrize(
    "messages, expected_range",
    [
        (["Hello", "How are you?"], (0, 0.5)),
        (["You're an idiot"], (0.5, 1)),
        (["I love this!"], (0, 0.3)),
    ],
)
def test_classify_specific_cases(messages, expected_range):
    result = classify(messages)
    assert expected_range[0] <= result <= expected_range[1]


def test_process(sample_user_messages):
    result = process(sample_user_messages, top=3)

    assert isinstance(result, list)
    assert len(result) == 3
    assert all(user in sample_user_messages.keys() for user in result)

    scores = [classify(sample_user_messages[user]) for user in result]
    assert scores == sorted(scores)


@pytest.mark.parametrize(
    "input_dict, expected_length",
    [
        ({}, 0),
        ({"user1": ["Test message"]}, 1),
    ],
)
def test_process_edge_cases(input_dict, expected_length):
    result = process(input_dict)
    assert len(list(result)) == expected_length


def test_process_top_parameter(sample_user_messages):
    for top in range(1, 6):
        result = process(sample_user_messages, top=top)
        assert len(list(result)) == top


@pytest.mark.parametrize("top", [1, 3, 5])
def test_process_order(sample_user_messages, top):
    result = process(sample_user_messages, top=top)
    scores = [classify(sample_user_messages[user]) for user in result]
    assert scores == sorted(scores)
