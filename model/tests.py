import pytest
import numpy as np
from processing import (
    classify,
    process,
    get_scores
)


@pytest.fixture
def sample_user_messages():
    return {
        "user1": 
        ["Hello", "How are you?"],
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


# def test_process(sample_user_messages):
#     result = process(sample_user_messages)

#     assert isinstance(result, list)
#     assert all(user in sample_user_messages.keys() for user in result)

#     scores = [classify(sample_user_messages[user]) for user in result]
#     assert scores == sorted(scores)


@pytest.mark.parametrize(
    "input_dict, expected_length, expected_output",
    [
        ({}, 0, []),  # Expecting an empty output for an empty input
        ({"user1": ["Test message"]}, 1, ["user1"]),  # Example output structure
    ],
)
def test_process_edge_cases(input_dict, expected_length, expected_output):
    result = get_scores(input_dict)
    
    # Convert result to a list to check its length and content
    result_list = list(result)
    
    # Assert that the length of the result matches the expected length
    assert len(result_list) == expected_length, f"Expected length {expected_length}, but got {len(result_list)}"
    
    # Assert that the result matches the expected output
    assert result_list == expected_output, f"Expected {expected_output}, but got {result_list}"
