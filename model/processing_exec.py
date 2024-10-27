import pandas as pd
from processing import process

df = pd.read_csv('/app/data/input/input.csv')
result_dict = df.groupby('from')['text'].apply(list).to_dict()
process(result_dict) 
