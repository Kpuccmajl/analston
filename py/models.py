from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.externals import joblib
import pandas as pd
import sys

# Read dataset
dataset = pd.read_csv('data.csv', index_col=0).dropna()
count_vectorizer = CountVectorizer(analyzer = "word", ngram_range = (1,3)) 
X = count_vectorizer.fit_transform(dataset['text'])
y = dataset['label']

#Create model
model = MultinomialNB()
model.fit(X, y)

#joblib.dump(model, 'model.sav')
#model = joblib.load('model.sav')

cv = count_vectorizer.transform(sys.argv[1:])
print(model.predict(cv).mean())