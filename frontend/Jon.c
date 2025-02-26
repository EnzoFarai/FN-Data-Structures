#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_QUESTIONS 10
#define XP_PER_CORRECT_ANSWER 10
#define XP_DEDUCTION_PER_WRONG_ANSWER 2
#define MIN_XP 1
#define MAX_XP 120
#define MAX_HEARTS 5
#define GEMS_PER_QUESTION 1

typedef struct {
    char question[256];
    char options[4][64];
    int correct_answer; // Index of the correct option (0-3)
    char explanation[256]; // Explanation for the correct answer
} QuizQuestion;

typedef struct {
    QuizQuestion questions[NUM_QUESTIONS];
    int incorrect_answers[NUM_QUESTIONS]; // Tracks incorrect answers
    int total_incorrect;
    int xp_earned;
    int pass_percentage;
    int hearts;
    int gems_earned;
} Quiz;

void initializeQuiz(Quiz *quiz) {
    QuizQuestion q1 = {"What is a data structure?", {"A programming language", "A way to organize and store data efficiently", "A method of software testing", "A type of computer hardware"}, 1, "A data structure is a way to organize data in a computer to perform operations efficiently, optimizing space and time complexity."};
    QuizQuestion q2 = {"Which of the following is NOT a benefit of using data structures?", {"Efficient data management", "Increased memory usage", "Better problem-solving capability", "Scalability for large applications"}, 1, "A well-designed data structure reduces memory usage by efficiently managing data, contrary to increasing memory consumption."};
    QuizQuestion q3 = {"What is an example of an application where arrays are commonly used?", {"Implementing undo operations", "Image processing", "Network routing", "Social media friend recommendations"}, 1, "Arrays store data in a fixed, sequential manner, making them suitable for applications like image processing and matrix operations."};
    QuizQuestion q4 = {"Why are linked lists preferred over arrays in dynamic memory allocation?", {"They are easier to implement", "They require less memory", "They allow efficient insertion and deletion", "They are faster for searching data"}, 2, "Unlike arrays, linked lists do not require contiguous memory, making insertion and deletion operations more efficient."};
    QuizQuestion q5 = {"Which data structure is best suited for handling real-time task scheduling?", {"Stack", "Queue", "Graph", "Array"}, 1, "Queues follow the FIFO (First In, First Out) principle, making them ideal for handling real-time scheduling tasks like job execution."};
    QuizQuestion q6 = {"What is the time complexity of searching in a hash table (on average)?", {"O(n)", "O(log n)", "O(1)", "O(n²)"}, 2, "Hash tables allow constant-time (O(1)) average-case search performance using key-value mappings."};
    QuizQuestion q7 = {"Which data structure is typically used for implementing undo functionality in text editors?", {"Stack", "Queue", "Linked List", "Tree"}, 0, "Stacks use the LIFO (Last In, First Out) principle, making them perfect for tracking undo operations."};
    QuizQuestion q8 = {"Which data structure is commonly used in graph traversal algorithms like Dijkstra’s shortest path?", {"Queue", "Stack", "Heap", "Hash Table"}, 2, "Heaps are used in priority queues, which help efficiently select the next shortest path in Dijkstra’s algorithm."};
    QuizQuestion q9 = {"How does a tree data structure help in organizing hierarchical data?", {"It stores data sequentially", "It represents relationships in a parent-child format", "It only allows fixed-size data storage", "It follows a last-in, first-out (LIFO) principle"}, 1, "Trees organize data hierarchically, making them ideal for file systems and decision-making processes."};
    QuizQuestion q10 = {"Which data structure is most efficient for storing frequently accessed data in a cache system?", {"Array", "Stack", "Hash Table", "Queue"}, 2, "Hash tables provide fast lookups and efficient data retrieval, making them ideal for caching frequently accessed data."};

    quiz->questions[0] = q1;
    quiz->questions[1] = q2;
    quiz->questions[2] = q3;
    quiz->questions[3] = q4;
    quiz->questions[4] = q5;
    quiz->questions[5] = q6;
    quiz->questions[6] = q7;
    quiz->questions[7] = q8;
    quiz->questions[8] = q9;
    quiz->questions[9] = q10;

    quiz->total_incorrect = 0;
    quiz->xp_earned = 0;
    quiz->pass_percentage = 0;
    quiz->hearts = MAX_HEARTS;
    quiz->gems_earned = 0;
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        quiz->incorrect_answers[i] = 0;
    }
}

void shuffleQuestions(QuizQuestion *questions, int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        QuizQuestion temp = questions[i];
        questions[i] = questions[j];
        questions[j] = temp;
    }
}

void runQuiz(Quiz *quiz) {
    shuffleQuestions(quiz->questions, NUM_QUESTIONS);

    printf("Welcome to the Data Structures Quiz!\n");
    printf("You will be asked %d questions. Good luck!\n\n", NUM_QUESTIONS);

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        printf("Question %d: %s\n", i + 1, quiz->questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'a' + j, quiz->questions[i].options[j]);
        }

        char user_answer;
        printf("Your answer: ");
        scanf(" %c", &user_answer);

        int user_choice = user_answer - 'a';
        if (user_choice == quiz->questions[i].correct_answer) {
            quiz->xp_earned += XP_PER_CORRECT_ANSWER;
        } else {
            quiz->incorrect_answers[i] = 1;
            quiz->total_incorrect++;
            quiz->hearts--;
            printf("Incorrect! Explanation: %s\n\n", quiz->questions[i].explanation);
        }

        if (quiz->hearts == 0) {
            printf("You've run out of hearts! Game over.\n");
            break;
        }
    }

    // Calculate XP and pass percentage
    if (quiz->xp_earned < MIN_XP) quiz->xp_earned = MIN_XP;
    quiz->pass_percentage = (int)(((float)(NUM_QUESTIONS - quiz->total_incorrect) / NUM_QUESTIONS) * 100;
    quiz->gems_earned = (NUM_QUESTIONS - quiz->total_incorrect) * GEMS_PER_QUESTION;

    // Display results
    printf("\nQuiz Results:\n");
    printf("Total XP Earned: %d\n", quiz->xp_earned);
    printf("Total Incorrect Answers: %d\n", quiz->total_incorrect);
    printf("Pass Percentage: %d%%\n", quiz->pass_percentage);
    printf("Gems Earned: %d\n", quiz->gems_earned);
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    runQuiz(&quiz);
    return 0;
}
