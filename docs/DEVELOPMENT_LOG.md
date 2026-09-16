## 12 September 2026

### What I Worked On

I returned to the 6502 Microprocessor Emulator project after a long break. Since I had been away from the project for quite some time, I first started trying to remember the overall C++ concepts, the project structure, the existing codebase, the functions and helper functions, and the overall logic behind how everything works together.

I continued following the **Dave poo — Tutorial Four** of the tutorial series. While going through the existing code, I had already cleaned up some parts of the code and organized the namespace so that it would be easier to find and understand the different parts of the project.

I also worked on regrouping the load instructions for **LDA, LDX, and LDY**, with the aim of making the common behavior reusable across the three load instructions for the same addressing mode instead of repeating similar test logic.

### Test Suite Refactoring

The existing GoogleTest file had grown to around **500 lines of code**. Because of its size and because I am returning to the project after a long break, I decided to create the test file again from scratch.

The purpose of doing this is not only to clean up the test code, but also to help me remember the project properly by writing the tests myself and understanding what each part of the test suite is doing.

I will keep the existing test file as a reference while rebuilding the new test file.

### C++ Concepts Reviewed

While working on the project, I made several notes and revised some of the basic C++ concepts that are being used in the project.

These included:

* Functions and function behavior
* Classes
* Structures
* Understanding how the different parts of the C++ program are organized
* Access specifiers:

  * `public`
  * `private`
  * `protected`
* C++ naming conventions:

  * UPPER_SNAKE_CASE
  * PascalCase
  * camelCase
  * snake_case

Reviewing these concepts is helping me understand the existing emulator code instead of simply following or reproducing it.

### Current Progress

The main focus at this point is rebuilding the GoogleTest file in a cleaner and more reusable structure.

I am working through the existing tests and understanding the logic behind the helper functions before writing the new test suite.

### Next Step

After taking a break today, I am continuing the work on **12 September itself**.

The next task is to continue and complete the updated/new GoogleTest file by rebuilding the tests from scratch and making sure I understand the structure and logic behind each part.

### Sign-Off

**Time:** 2:50 PM

Signing off for this session.

## **16 September 2026**

### **What I Worked On**

Today I continued working on the **6502 Microprocessor Emulator**, mainly focusing on simplifying, debugging, and improving the new GoogleTest file that I have been rebuilding.

While working on the new test file, I encountered several minor bugs and syntax errors. I went through them one by one, understood what was causing the problems, and fixed them. This helped me make the new test file cleaner and easier to understand instead of simply trying to reproduce the older test file.

The work done today was relatively small compared with a heavy implementation session, but it was useful because I was able to make the new test structure more stable and continue understanding the project.

### **Working Consistently on the Project**

I had decided that I would work on this project every day for around **2–3 hours** so that I could maintain a consistent development streak.

However, I have realized that I have not been able to maintain that level of focused work when I am at home alone. I generally find it easier to concentrate on the project when I am at college, particularly after my classes are finished.

There was also a holiday between **13 September and 15 September**, which interrupted the continuity of my work. Today, since I was back at college, I was able to continue working on the emulator.

Going forward, I want to focus less on forcing a specific number of hours and more on maintaining the habit of **doing some meaningful work on the project every day after college**. This will allow me to maintain both my college attendance and my project-development streak.

### **Test Suite Refactoring**

I have continued rebuilding the new GoogleTest file in a simplified and reusable structure.

For now, I have mainly implemented the **basic/general CPU tests** and several **helper functions**, including helpers related to checking CPU flags and other common test behavior.

The current work is primarily focused on the three load instructions:

* **LDA**
* **LDX**
* **LDY**

The purpose of the refactoring is to avoid writing almost identical tests separately for each instruction and instead create reusable test logic that can be applied to the relevant load instructions.

### **C++ Concepts Reviewed**

While debugging and refactoring the test file, I also revised some C++ concepts that had caused confusion during the implementation.

One of these was the difference between using the **dot (`.`)** and **arrow (`->`) operators**, particularly in relation to objects and pointers.

I also revised the concept of **BDC and standard binary representation**, since I had some confusion about these concepts while working with the 6502 emulator.

These smaller conceptual revisions are important because I want to understand why the code works rather than simply make the tests compile.

### **Development Log and README**

Along with the code, I also rewrote parts of my **development log** and **README file**.

The intention is to make the documentation more active, organized, and professional as the project develops.

I had not pushed the work from **12 September** to GitHub because I initially thought I would first complete the new test file and then push everything together.

However, I now realize that the refactoring and rebuilding of the test file is a much longer process than I initially expected. Therefore, rather than waiting until the entire test suite is completed, I am going to push the progress that has already been made.

This will also provide a proper record of the development progress on GitHub.

### **Current Load Instruction Test Plan**

At present, my main focus is on refactoring the tests for the different addressing modes used by the load instructions.

The seven main addressing modes I am working with are:

1. **Immediate**
2. **Zero Page**
3. **Zero Page, X**
4. **Zero Page, Y**
5. **Absolute**
6. **Absolute, X**
7. **Absolute, Y**

The goal is to make the common test structure reusable across **LDA, LDX, and LDY**, wherever those addressing modes are applicable.

There are also:

* **Indexed Indirect, X**
* **Indirect Indexed, Y**

which are relevant to **LDA**.

I also noticed that **Zero Page, Y** is specifically associated with **LDX**, while the indirect addressing modes are specifically associated with **LDA**. I will research and verify these instruction/addressing-mode relationships further before deciding how they should be represented in the refactored test structure.

### **Current Progress**

So far, the refactored test suite contains the **general CPU tests** and the initial reusable **helper functions**.

The work is currently centered around creating a structure where the common load-instruction testing logic can be reused rather than duplicated.

The immediate goal is therefore not to implement every test at once, but to first establish a clean and understandable testing framework and then expand it across the remaining load instructions and addressing modes.

### **Next Step**

Tomorrow I plan to continue with the **load-instruction tests**.

The main target will be to work through the addressing modes systematically and refactor the tests so that the same testing logic can be used for the applicable **LDA, LDX, and LDY** instructions.

I had also planned to work on the **BIT instruction** today, but I do not think I will be able to implement it properly in this session. Therefore, I will most likely continue with it tomorrow after completing the current load-instruction work.

### **GitHub Progress**

I am also going to push the current development to **GitHub** instead of waiting until the entire test file is finished.

This is important because the current work already represents a significant part of the refactoring process, and keeping regular commits will provide a better development history for the project.

### **Sign-Off**

**Time:** 2:41 PM
