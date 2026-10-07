#include <iostream>
#include <string>

using namespace std;

// Node representing a single Print Job
struct PrintJob {
    int jobID;
    string docName;
    int pages;
    PrintJob* next;

    PrintJob(int id, string name, int p) {
        jobID = id;
        docName = name;
        pages = p;
        next = NULL;
    }
};

// Queue representation with Front and Rear pointers
struct PrinterQueue {
    PrintJob* front;
    PrintJob* rear;
    int totalJobs;

    PrinterQueue() {
        front = NULL;
        rear = NULL;
        totalJobs = 0;
    }

    // IsEmpty
    bool isEmpty() {
        return front == NULL;
    }

    // Count Jobs
    int countJobs() {
        return totalJobs;
    }

    // Add Job (Insert at Rear)
    void addJob(int id, string name, int pages) {
        PrintJob* newJob = new PrintJob(id, name, pages);

        // Case 1: Empty queue
        if (isEmpty()) {
            front = newJob;
            rear = newJob;
        } 
        // One or more jobs already waiting
        else {
            rear->next = newJob; // Old rear points to new job
            rear = newJob;       // Rear moves to new job
        }

        totalJobs++;
        cout << ">> Added Job: [" << id << "] " << name << " (" << pages << " pages)" << endl;
    }

    // Process Job 
    void processJob() {
        if (isEmpty()) {
            cout << ">> Error: Queue is empty. No jobs to process!" << endl;
            return;
        }

        PrintJob* temp = front;

        cout << ">> [PROCESSING] Job ID: " << temp->jobID 
             << " | Document: " << temp->docName 
             << " | Pages: " << temp->pages << endl;

        // Move front to next job
        front = front->next;

        // If the queue only had 1 job and is now empty, rear must also become NULL
        if (front == NULL) {
            rear = NULL;
        }

        delete temp; // Free memory
        totalJobs--;
    }

    //  View Next Job (Peek at Front without removing)
    void viewNextJob() {
        if (isEmpty()) {
            cout << ">> Queue is empty. No upcoming jobs." << endl;
            return;
        }

        cout << ">> Next Job to Print: [" << front->jobID << "] " 
             << front->docName << " (" << front->pages << " pages)" << endl;
    }
    void displayQueue() {
        if (isEmpty()) {
            cout << ">> Printer Queue is currently empty." << endl;
            return;
        }

        cout << "\n--- Current Waiting Queue (Total: " << totalJobs << ") ---" << endl;
        PrintJob* curr = front;
        int pos = 1;
        while (curr != NULL) {
            cout << pos++ << ". [ID: " << curr->jobID << "] " 
                 << curr->docName << " - " << curr->pages << " pages";
            if (curr == front) {
                cout << " <-- (FRONT / NEXT)";
            }
            if (curr == rear) {
                cout << " <-- (REAR)";
            }
            cout << endl;
            curr = curr->next;
        }
        cout << "------------------------------------------" << endl;
    }
// Clear Queue (Free all nodes)
    void clearQueue() {
        while (!isEmpty()) {
            PrintJob* temp = front;
            front = front->next;
            delete temp;
        }
        rear = NULL;
        totalJobs = 0;
    }

    ~PrinterQueue() {
        clearQueue();
    }
};
int main() {
    PrinterQueue pq;

    cout << "================ PRINTER JOB SCHEDULER ================\n" << endl;
    pq.addJob(101, "Assignment1.pdf", 10);
    pq.addJob(102, "Report.docx", 25);
    pq.addJob(103, "Notes.pdf", 5);
    pq.addJob(104, "LabTask.docx", 15);

    //Display all jobs
    cout << "\nStep 1: Displaying all jobs:" << endl;
    pq.displayQueue();
    cout << "\nStep 2: Processing two jobs:" << endl;
    pq.processJob();
    pq.processJob();
    cout << "\nStep 3: Displaying remaining jobs:" << endl;
    pq.displayQueue();
    cout << "\nStep 4: Adding a new job:" << endl;
    pq.addJob(105, "Thesis.pdf", 50);
    cout << "\nStep 5: Viewing next job:" << endl;
    pq.viewNextJob();
    cout << "\nStep 6: Processing all remaining jobs:" << endl;
    while (!pq.isEmpty()) {
        pq.processJob();
    }
    cout << "\nStep 7: Attempting to process from empty queue:" << endl;
    pq.processJob();

    return 0;
}