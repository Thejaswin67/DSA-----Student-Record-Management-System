// ============================================================
// STUDENT RECORD MANAGEMENT SYSTEM - WEB INTERFACE
// ============================================================

let students = JSON.parse(localStorage.getItem("students")) || [
    {
        id: "412625205046",
        name: "Thejaswin S",
        age: 19,
        department: "Information Technology",
        marks: 85,
        phone: "9360682183"
    },
    {
        id: "412625104080",
        name: "Tamilselvan M",
        age: 19,
        department: "Computer Science Engineering",
        marks: 80,
        phone: "9000000001"
    },
    {
        id: "412625104089",
        name: "Yuvaraj A",
        age: 19,
        department: "Computer Science Engineering",
        marks: 72,
        phone: "9000000002"
    },
    {
        id: "412625205009",
        name: "Charulatha S",
        age: 19,
        department: "Information Technology",
        marks: 90,
        phone: "9000000003"
    }
];

let originalOrder = [...students];

saveStudents();
displayStudents();

// ============================================================
// SAVE STUDENTS
// ============================================================

function saveStudents() {
    localStorage.setItem("students", JSON.stringify(students));
}

// ============================================================
// GET GRADE
// F : Below 50
// C : 50 - <70
// B : 70 - <90
// A : 90 - 100
// ============================================================

function getGrade(marks) {
    marks = Number(marks);

    if (marks < 50) {
        return "F";
    } else if (marks < 70) {
        return "C";
    } else if (marks < 90) {
        return "B";
    } else {
        return "A";
    }
}

// ============================================================
// GET MARKS RANGE
// ============================================================

function getMarksRange(marks) {
    marks = Number(marks);

    if (marks < 50) {
        return "Below 50";
    } else if (marks < 70) {
        return "50 - <70";
    } else if (marks < 90) {
        return "70 - <90";
    } else {
        return "90 - 100";
    }
}

// ============================================================
// GET GRADE VALUE FOR SORTING
// F = 1, C = 2, B = 3, A = 4
// ============================================================

function getGradeValue(marks) {
    const grade = getGrade(marks);

    if (grade === "A") return 4;
    if (grade === "B") return 3;
    if (grade === "C") return 2;
    return 1;
}

// ============================================================
// DISPLAY STUDENTS
// ============================================================

function displayStudents(list = students) {
    const table = document.getElementById("studentTable");

    if (!table) return;

    table.innerHTML = "";

    list.forEach(function(student) {
        const grade = getGrade(student.marks);
        const range = getMarksRange(student.marks);

        const row = document.createElement("tr");

        row.innerHTML = `
            <td>${safe(student.id)}</td>
            <td>${safe(student.name)}</td>
            <td>${student.age}</td>
            <td>${safe(student.department)}</td>
            <td>${Number(student.marks).toFixed(1)}</td>
            <td>
                <span class="grade-badge grade-${grade.toLowerCase()}">
                    ${grade}
                </span>
            </td>
            <td>${range}</td>
            <td>${safe(student.phone)}</td>
            <td>
                <button class="action-btn"
                    onclick="deleteStudent('${encodeURIComponent(student.id)}')">
                    Delete
                </button>
            </td>
        `;

        table.appendChild(row);
    });

    updateStatistics();
    updateGradeCounts();
}

// ============================================================
// FILTER STUDENTS BY GRADE
// ============================================================

function filterByGrade(selectedGrade) {
    const filteredStudents = students.filter(function(student) {
        return getGrade(student.marks) === selectedGrade;
    });

    displayStudents(filteredStudents);

    const message = document.getElementById("filterMessage");

    if (message) {
        message.textContent =
            `${selectedGrade} Rank: ${filteredStudents.length} student(s) found.`;
    }
}

// ============================================================
// SHOW ALL STUDENTS
// ============================================================

function showAllStudents() {
    displayStudents(students);

    const message = document.getElementById("filterMessage");

    if (message) {
        message.textContent = `Showing all ${students.length} student(s).`;
    }
}

// ============================================================
// UPDATE GRADE COUNTS
// ============================================================

function updateGradeCounts() {
    let countA = 0;
    let countB = 0;
    let countC = 0;
    let countF = 0;

    students.forEach(function(student) {
        const grade = getGrade(student.marks);

        if (grade === "A") {
            countA++;
        } else if (grade === "B") {
            countB++;
        } else if (grade === "C") {
            countC++;
        } else {
            countF++;
        }
    });

    document.getElementById("countA").textContent = countA;
    document.getElementById("countB").textContent = countB;
    document.getElementById("countC").textContent = countC;
    document.getElementById("countF").textContent = countF;
}

// ============================================================
// ADD STUDENT
// ============================================================

document.getElementById("studentForm")?.addEventListener(
    "submit",
    function(event) {
        event.preventDefault();

        const newStudent = {
            id: document.getElementById("id").value.trim(),
            name: document.getElementById("name").value.trim(),
            age: Number(document.getElementById("age").value),
            department: document.getElementById("department").value.trim(),
            marks: Number(document.getElementById("marks").value),
            phone: document.getElementById("phone").value.trim()
        };

        const message = document.getElementById("message");

        if (newStudent.marks < 0 || newStudent.marks > 100) {
            message.textContent = "Marks must be between 0 and 100.";
            message.className = "error-message";
            return;
        }

        const exists = students.some(function(student) {
            return student.id === newStudent.id;
        });

        if (exists) {
            message.textContent = "Student ID already exists.";
            message.className = "error-message";
            return;
        }

        students.push(newStudent);
        saveStudents();
        displayStudents();

        message.textContent =
            `Student added successfully. Grade: ${getGrade(newStudent.marks)} | Range: ${getMarksRange(newStudent.marks)}`;
        message.className = "success-message";

        this.reset();
        originalOrder = [...students];

        location.hash = "records";
    }
);

// ============================================================
// SEARCH STUDENT
// ============================================================

function searchStudent() {
    const id = document.getElementById("searchId").value.trim();

    const student = students.find(function(item) {
        return item.id === id;
    });

    const result = document.getElementById("searchResult");

    if (!student) {
        result.innerHTML = `<div class="result not-found">Student not found.</div>`;
        return;
    }

    const grade = getGrade(student.marks);
    const range = getMarksRange(student.marks);

    result.innerHTML = `
        <div class="result">
            <h3>Student Found</h3>
            <p><strong>ID:</strong> ${safe(student.id)}</p>
            <p><strong>Name:</strong> ${safe(student.name)}</p>
            <p><strong>Age:</strong> ${student.age}</p>
            <p><strong>Department:</strong> ${safe(student.department)}</p>
            <p><strong>Marks:</strong> ${Number(student.marks).toFixed(1)}</p>
            <p><strong>Grade:</strong>
                <span class="grade-badge grade-${grade.toLowerCase()}">${grade}</span>
            </p>
            <p><strong>Marks Range:</strong> ${range}</p>
            <p><strong>Phone:</strong> ${safe(student.phone)}</p>
        </div>
    `;
}

// ============================================================
// DELETE STUDENT
// ============================================================

function deleteStudent(encodedId) {
    const id = decodeURIComponent(encodedId);

    if (!confirm("Delete this student record?")) {
        return;
    }

    students = students.filter(function(student) {
        return student.id !== id;
    });

    originalOrder = [...students];

    saveStudents();
    displayStudents();
}

// ============================================================
// SORT BY MARKS DESCENDING
// ============================================================

function sortByMarksDescending() {
    bubbleSort(function(a, b) {
        return Number(a.marks) < Number(b.marks);
    });

    showAllStudents();
    showSortMessage("Sorted by Marks: Highest to Lowest");
}

// ============================================================
// SORT BY MARKS ASCENDING
// ============================================================

function sortByMarksAscending() {
    bubbleSort(function(a, b) {
        return Number(a.marks) > Number(b.marks);
    });

    showAllStudents();
    showSortMessage("Sorted by Marks: Lowest to Highest");
}

// ============================================================
// SORT BY RANGE DESCENDING
// A -> B -> C -> F
// ============================================================

function sortByRangeDescending() {
    bubbleSort(function(a, b) {
        const gradeA = getGradeValue(a.marks);
        const gradeB = getGradeValue(b.marks);

        if (gradeA !== gradeB) {
            return gradeA < gradeB;
        }

        return Number(a.marks) < Number(b.marks);
    });

    showAllStudents();
    showSortMessage("Sorted by Grade / Range: A → B → C → F");
}

// ============================================================
// SORT BY RANGE ASCENDING
// F -> C -> B -> A
// ============================================================

function sortByRangeAscending() {
    bubbleSort(function(a, b) {
        const gradeA = getGradeValue(a.marks);
        const gradeB = getGradeValue(b.marks);

        if (gradeA !== gradeB) {
            return gradeA > gradeB;
        }

        return Number(a.marks) > Number(b.marks);
    });

    showAllStudents();
    showSortMessage("Sorted by Grade / Range: F → C → B → A");
}

// ============================================================
// BUBBLE SORT
// ============================================================

function bubbleSort(shouldSwap) {
    for (let i = 0; i < students.length - 1; i++) {
        let swapped = false;

        for (let j = 0; j < students.length - i - 1; j++) {
            if (shouldSwap(students[j], students[j + 1])) {
                const temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) {
            break;
        }
    }

    saveStudents();
    displayStudents();
}

// ============================================================
// SORT MESSAGE
// ============================================================

function showSortMessage(message) {
    const element = document.getElementById("sortMessage");

    if (element) {
        element.textContent = message;
    }
}

// ============================================================
// STATISTICS
// ============================================================

function updateStatistics() {
    const total = document.getElementById("total");
    const highest = document.getElementById("highest");
    const average = document.getElementById("average");

    if (!total) return;

    total.textContent = students.length;

    if (students.length === 0) {
        highest.textContent = "0";
        average.textContent = "0";
        return;
    }

    const marks = students.map(function(student) {
        return Number(student.marks);
    });

    const max = Math.max(...marks);

    const avg = marks.reduce(function(sum, mark) {
        return sum + mark;
    }, 0) / marks.length;

    highest.textContent = max.toFixed(1);
    average.textContent = avg.toFixed(2);
}

// ============================================================
// SAFE HTML OUTPUT
// ============================================================

function safe(value) {
    return String(value)
        .replaceAll("&", "&amp;")
        .replaceAll("<", "&lt;")
        .replaceAll(">", "&gt;")
        .replaceAll('"', "&quot;")
        .replaceAll("'", "&#039;");
}
