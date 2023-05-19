import pandas as pd

df = pd.read_csv("list_of_kskl_events.csv")
df_clean = df.drop_duplicates()
df_clean.to_csv('new_list.csv', index=False)

