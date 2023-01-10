# Assignment 4: Search Engine 

This is a longer group project! Here are the [Project Instructions](Project_Instructions.pdf).


**Objectives:**

* Work in a team using version control.
* Design a larger system, plan the implementation and submit multiple deliverables.
* Implement a search tree-based map.
* Implement a persistent data structure.


## Timeline 

You have about four weeks to complete the assignment. Start right away! **The lab TA will expect that you already have most of that week's work completed. Come with prepared questions and
be prepared to answer the TA's questions about your code.**

Suggested timeline (see Canvas for early deliverables):

* Week 1: Plan your timeline (see below); design you solution (first UML class diagram); 
    adapt the AVL tree from class to work as a map suitable for the inverted file index and provide tests (Catch2 test would be great).
* Week 2: Implement the document parser; build the indices. 
* Week 3: Implement the query processor; user interface; and add persistence to the index.
* Week 4: Finish code and write the documentation file.

# Submission 

In addition to the code, you need to submit a markdown document called `documentation.md` containing the following information (You can copy and paste the section structure below):

High-level Design of Solution
UML class diagram, etc.
High-level pseudocode for each component.
https://lucid.app/lucidchart/cce65ccc-a0d7-4aac-84b7-3f0ebbfd4dba/edit?viewport_loc=-1838%2C-1461%2C5200%2C3007%2CHWEp-vi-RSFO&invitationId=inv_8070460d-0b5b-4fa0-9d69-889c70413897


Your Timeline to Finish the Project
Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.
TASK              |    PLANNED COMPLETION    |   ACTUAL COMPLETION      |  TIME SPENT BY REESE IN HOURS | TIME SPENT BY NICO IN HOURS
UML Diagram       |    Nov 5                 |    Nov 3                 |    5.0 (redid like 6 times)   |       2.0
ALVTree           |    Nov 10                |    Nov 20 (had to redo)  |              5.5              |       1.5
document          |    Nov 15                |    Nov 20 (had to redo)  |              5.5              |       1.0
indexHandler      |    Nov 15                |    Nov 20                |              2.0              |       9.0
porter stemmer    |    Nov 25                |    Nov 30                |              0.0              |       0.0 (taken from another program
queryProcessor    |    Nov 30                |    Dec 4                 |              1.0              |       2.0
stopFunction      |    Dec 2                 |    Dec 4                 |              1.5              |       0.5
word              |    Dec 2                 |    Dec 4                 |              1.5              |       1.0
main              |    Nov 10                |    Nov 20 (had to redo)  |              0.0              |       0.5
NOTE FOR GRADER: We tried to make our own AVL Tree but then were told by a TA we could use Professor Hahsler's.

Used Data Structures
Explanation of what data structures are used where. For each, state - time and space complexity (Big-Oh), - why it is the appropriate data structure and what other data structure could have been used.

AVLTree: The basic nodes and the entire binary search tree are data structures. This means that the big-Oh notation of the data structure is O(n). This is the appropriate data sturcture to use as the
program calls students to create a blanced binary search tree. You could technically use a vector to complete the work, but there is a large chance that the operating system would die before processing all of the .json files.

Document:  The document class uses a wrapper class, object, and vector. The object is O(n). the vector is o(g(n)), and the wrapper class is O(n). We could have used a list for the vector; however, we needed to keep the class consistent with other classes, which were already using vectors when document was created. The wrapper class was a ncessity for parsing the .json files.


indexHandler: The indexHandler uses a binary search tree and vector. The binary search tree has a Big-Oh of O(n), while the vector has a Big-Oh of O(g(n)). The tree was necessary as it was required for the project; however, we could have used a list in place of a vector to increase time efficiency.

porter stemmer: For the stemmer we used repository on github. All the relevant documentation for this repository is listed in the files we used from it. The link to this repository is https://github.com/smassung/porter2_stemmer.git

queryProcessor: The only data structure in the class is an Object, which holds a Big-Oh notation of O(n). We technically could have used a multilayered vector to hold this data, but
it would have been a lot more tedious. An object allows information to be thrown into one location and may be used in a variety of ways later in which we could not have used
a vector for.

stopFunction: stopFunction only uses basic variables and a static object; thus, the big-oh notation of the data structures were O(n). We used a static object here to prevent the class from rebuilding the same list of stop words over and over again in an effort to save time during indexing.

word: An object and vector are the only data structures in this class. The Big-Oh notation for a vector is O(g(n)), while the big-oh notation for an object is O(n).
It would have most likely been better for us to use a list for time efficiency, but we understood vectors to a greater extent and found them easier to use in such a large project.

main: The only data structure used in this part of the program is an object. The main function takes an object and throws it into startEngine, which then begins the program. Thus,
the big-oh notation of this function is O(n). There is no other way that we could have completed the maiun function.



## User Documentation
How to use the software.
The user interface for this program is pretty bare bones. When starting the program you should already have the path to the file you want to index ready. other than that follow the instructions given by the program.

Some example queries with the results.

## Performance
Statistics for indexing all documents and timing.
unfortunately it takes over 2 hours to index all the files, we spent too much time working with small datasets and by the time we were testing it with the full dataset we didn't have much time to work on improving the speed.

## Automatic Tests and Memory Tests

Tests for your AVL tree's function
since we did use the AVL tree we worked on in class we didn't do extensive testing on the functions themselves.

Tests for indexer 
the index handler was tricky to test since it is essentially the backbone of the program. every time a new element was finished we had to go back to the index handler and make sure everyting was still working as intended. 

Tests for the complete system 
Overall during the course of this program we did not utalize Catch2 nearly as much as we should have, instead we spent a lot of time in the terminal with temporary cout statements. I think we as a team could definetly stand to benifit from becoming more comfortable with Catch2 because it could have made testing much more efficient.

## Grading Rubric

| Task                        | Points Possible | Points Awarded |
| :------------------         | --------------: | -------------: |
| UML diagram/design          | 10              |                |
| AVL tree map + tests        | 20              |                |
| AVL tree persistence + tests| 10              |                |
| Document parser             | 10              |                |
| Query processor + interface | 20              |                |
| Proper Memory Management    | 5               |                |
| Formatting, Comments, etc.  | 5               |                |
| Documentation               | 20              |                |
| 48hr early submission bonus | +5              |                |

