import pytest
from unittest.mock import patch
from processing import (
    classify,
    write_into_file,
)


@pytest.mark.parametrize(
    "messages, expected_range",
    [
        (["Hello"], (0.0, 0.4)),  # Non-aggressive
        (["I hate you!"], (0.4, 1.0)),  # Very aggressive
    ],
)
def test_classify_with_real_model(messages, expected_range):
    # Call classify with the provided messages
    score = classify(messages)

    # Assert that the score falls within the expected range
    assert expected_range[0] <= score <= expected_range[1]


# Mocking Detoxify's predict method
@pytest.fixture
def mock_detoxify():
    with patch("detoxify.Detoxify") as MockDetoxify:
        mock_instance = MockDetoxify.return_value
        yield mock_instance


@pytest.mark.parametrize(
    "mock_return_value, expected_mean",
    [
        ([0.1, 0.1, 0.1], 0.1),  # Example toxicity scores
        ([0.2, 0.3, 0.4], 0.3),  # Another set of scores
        ([0.5, 0.5, 0.5], 0.5),  # Uniform higher scores
        ([0.9, 0.8, 0.7], 0.8),  # High toxicity scores
    ],
)
def test_classify(mock_detoxify, mock_return_value, expected_mean):
    # Setup mock return value for predict based on parameterization
    mock_detoxify.predict.return_value = {"toxicity": mock_return_value}

    messages = ["Hello", "How are you?", "Goodbye"]

    # Call classify with the mocked Detoxify instance
    score = classify(messages, detoxify_model=mock_detoxify)

    assert score == pytest.approx(expected_mean, abs=0.001)


def test_write_into_file(tmp_path):
    user_scores = {"user1": 0.1, "user2": 0.4}

    output_file = tmp_path / "output_raw/new.txt"

    # Ensure the directory exists
    output_file.parent.mkdir(parents=True, exist_ok=True)

    write_into_file(str(output_file), user_scores)

    # Read back the file and check contents
    with open(output_file) as f:
        lines = f.readlines()

    assert lines == ["user1 0.1\n", "user2 0.4\n"]
