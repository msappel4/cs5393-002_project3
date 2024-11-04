# cs5393-002_project3
cs5393-002 project3 sentiment analysis

Megan Appel and Diego Mejia

Instructions on how to run code are in howtorun.txt file

A sentiment analyzer in C++ uses two key components: an Analyzer class and a DSString class. The DSString class is a dynamic string handler which manages operations like concatenation, substring extraction, and character manipulation. This class allows the analyzer to efficiently process input text for sentiment analysis. The Analyzer class contains methods to evaluate the sentiment of the input text. It utilizes positive and negative words, which it compares against the processed strings from the DSString class. As the Analyzer iterates through the input, it counts occurrences of these words to determine the overall sentiment score. The score helps classify the sentiment as positive or negative based on predefined thresholds. Additionally, the Analyzer class incorporates tokenization and stemming to enhance accuracy. 

Resources:
Chatgpt.com
Ria Mukherji
