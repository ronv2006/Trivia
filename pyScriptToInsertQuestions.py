import requests
from typing import List
import sqlite3

class Question:
    def __init__(self, question: str, correct_answer: str, choice1: str, choice2: str, choice3: str):
        self.question_text = question
        self.correct_answer = correct_answer
        self.choice1 = choice1
        self.choice2 = choice2
        self.choice3 = choice3

def get_questions() -> List[Question]:
    url = "https://opentdb.com/api.php?amount=50&type=multiple"
    response = requests.get(url)
    data = response.json()
    questions_data = data['results']
    questions = []
    for q in questions_data:
        question_text = q['question']
        correct_answer = q['correct_answer']
        incorrect_answers = q['incorrect_answers']
        question = Question(question_text, correct_answer, incorrect_answers[0], incorrect_answers[1], incorrect_answers[2])
        questions.append(question)

    return questions

def insert_questions_in_db(db_file_name: str, questions:List[Question]):
    connect = sqlite3.connect(db_file_name)
    myCursor = connect.cursor()
    for question in questions:
        print(question.question_text)
        sql_command = "INSERT INTO QUESTIONS (question, correctAnswer, wrongAns1, wrongAns2, wrongAns3) VALUES ('%s', '%s', '%s', '%s', '%s')" % (question.question_text, question.correct_answer, question.choice1, question.choice2, question.choice3)
        myCursor.execute(sql_command)
        connect.commit()
    connect.close()

def main():
    fifty_questions = get_questions()
    insert_questions_in_db("TriviaDB.sqlite", fifty_questions)
    while(True):
	    pass

if __name__ == "__main__":
	main()
