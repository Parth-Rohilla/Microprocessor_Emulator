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

## 17 September 2026

### What I Worked On

Today I completed the **refactoring task for the 6502 Microprocessor Emulator**. With this, **Tutorial Fourth video of the tutorial series is officially completed**.

The main focus was completing the refactoring of the GoogleTest file and cleaning up the existing project structure.

### Test Suite Refactoring

During the previous session, I decided to rebuild the GoogleTest file from scratch to better understand the project and its logic. However, after working on the new test file, I realized that I was making the test structure unnecessarily complicated by trying to combine too much logic into single tests and helpers.

Because of this, I changed my approach.

On the night of **16 September**, I went back to the earlier Git commit from around **30 June**, before the refactoring work had started. I restored only the original test file, **`main_6502_test.cpp`**, rather than reverting the entire project, so that the newer README, development log, and other project changes would remain intact.

The newer test file, **`m6502_CPU_test.cpp`**, has been kept but is no longer being used as the primary test file.

I then refactored the original test file extensively. Almost every line was changed or rewritten, making the final result feel effectively like a new test file while keeping the original testing approach simpler and more understandable.

I am satisfied with the result because the refactoring now improves the structure without unnecessarily complicating the tests.

### Load Instruction Refactoring

The refactoring has now been completed for the applicable addressing modes of:

* **LDA**
* **LDX**
* **LDY**

The common test logic was refactored for:

* Immediate
* Zero Page
* Zero Page, X
* Zero Page, Y
* Absolute
* Absolute, X
* Absolute, Y

I did not refactor **Indexed Indirect, X** and **Indirect Indexed, Y** because they are currently used only by **LDA** in the emulator.

I will handle these addressing modes later if they become relevant to other instructions such as store instructions. This also follows the approach used in the tutorial, where these addressing modes were not included in the same refactoring.

### Bug Fix

While working through the refactoring, I found a small bug in **`main_6502.cpp`**.

The **LDA Zero Page, X** instruction was missing one cycle in its implementation. I corrected the instruction so that it now uses the appropriate number of cycles.

### CMake and Test File Cleanup

I also updated the **CMake configuration** to remove the test file that I decided not to continue using, **`m6502_CPU_test.cpp`**.

Although that approach did not become part of the final implementation, experimenting with it was useful. It helped me understand what made the test structure unnecessarily complicated and gave me a clearer idea of how I want to approach the refactoring going forward.

### Current Progress

The refactoring task is now **complete**.

The main code has also been cleaned up and organized under the **`m6502` namespace**. The GoogleTest suite has been refactored into a simpler and more reusable structure, and the small LDA Zero Page, X cycle bug has been fixed.



### Next Step

With **Tutorial Four completed**, I can now move forward to the next part of the 6502 emulator proje
hat is the fifth video of toutorial i.e finally implementing the LDX and LDY instructions
T

### Sign-Off

**Time:** 11:15 PM
**Date:** 17 September 2026.

## 27 September 2026

### What I Worked On

Today I completed the **fifth tutorial video of the 6502 Microprocessor Emulator tutorial series** that I have been following. With this, the implementation of the **LDX and LDY load instructions** has been completed.

The fifth video was relatively short, around **30 minutes**, and mainly focused on implementing and refactoring the logic required for LDX and LDY. Although the actual implementation was fairly simple, I spent around **three hours** working through the video, understanding what was being done, comparing it with my existing code, and implementing the changes properly.

I started working at approximately **11:30 PM on 26 September** and finished at around **3:05 AM on 27 September**.

As with the previous tutorial, I am not following the tutorial completely one-to-one. There are some functions and improvements that were not implemented in the tutorial but that I have already implemented in my own project. Therefore, I first noted down the changes made in the video and then went through them one by one, adapting them to my own implementation rather than blindly copying everything.

### LDX and LDY Implementation

The main task for this session was completing the remaining load instructions for **LDX** and **LDY**.

I first implemented the **Immediate addressing mode** for both LDX and LDY. This was straightforward because Immediate addressing does not require an additional addressing-mode helper function.

While working on the load instructions, I also made a small cleanup to the existing code.

Previously, when loading a value into a register, I was sometimes creating an intermediate variable to store the result of a function and then assigning that variable to the register. This meant that the same operation required an unnecessary middle variable.

I changed this so that the register receives the result of the function directly.

For example, instead of using an intermediate value:

```cpp
u8 value = readByte(...);
X = value;
```

the operation can directly assign the returned value:

```cpp
X = readByte(...);
```

This does not make a major difference in the number of lines of code, but it removes an unnecessary variable and makes the code cleaner and more direct.

### Flag Function Cleanup

I also renamed the parameter used by the **Zero and Negative flag-setting function**.

Previously, I had named the parameter `value`. However, after looking at how the function was being used, I realized that what I was passing to the function was actually a **CPU register**, rather than a generic value.

Therefore, I changed the parameter name to better represent what the function is actually receiving.

This is a small change, but it makes the purpose of the function clearer and makes the code easier to understand.

### Addressing Mode Refactoring

After implementing the Immediate addressing mode, I continued refactoring the remaining addressing modes for LDX and LDY.

The process was fairly straightforward because most of the required logic had already been implemented for LDA and could be reused.

I refactored the required addressing modes including:

* Zero Page
* Zero Page, X
* Zero Page, Y
* Absolute
* Absolute, X
* Absolute, Y

One additional addressing mode needed to be implemented specifically for LDX: **Zero Page, Y**.

The logic for this was very similar to the existing Zero Page, X implementation. Therefore, I reused the existing structure and adapted it from X indexing to Y indexing.

After implementing the required addressing modes, I connected them to the corresponding LDX and LDY instructions and verified that the tests were working.

### Completion of Load Instructions

With today's work completed, **LDA, LDX, and LDY now have their applicable instructions and tests implemented**.

The common addressing-mode and testing logic has also been refactored so that the same functionality can be reused rather than duplicated for every instruction.

This completes the load-instruction portion of the project.

The overall progression is now:

```text
LDA
 ├── Immediate
 ├── Zero Page
 ├── Zero Page, X
 ├── Absolute
 ├── Absolute, X
 ├── Absolute, Y
 ├── Indexed Indirect, X
 └── Indirect Indexed, Y

LDX
 ├── Immediate
 ├── Zero Page
 ├── Zero Page, Y
 ├── Absolute
 └── Absolute, Y

LDY
 ├── Immediate
 ├── Zero Page
 ├── Zero Page, X
 ├── Absolute
 └── Absolute, X
```

The exact set of addressing modes differs between the instructions because the 6502 does not support every addressing mode for every load instruction.

### Tutorial Progress

With today's work, the **fifth tutorial video is officially completed**.

The tutorial itself was relatively short, but I still took time to understand what was being changed instead of simply copying the implementation. Since I have already made some changes and additions that differ from the tutorial, I adapted the tutorial's approach to fit the current structure of my emulator.

I also had another unexpected break in my development schedule because, as usual, the day became more hectic than expected. Even so, I was able to complete the entire task during this session.

### Current Progress

The implementation and testing of the **LDA, LDX, and LDY load instructions are now complete**.

The code has also become more reusable through the addressing-mode refactoring, and unnecessary intermediate variables have been removed from some of the instruction implementations.

With **Tutorial Five completed**, the next major decision is what direction to take the project next.

### Next Step

For the next session, I need to decide between two possible directions.

The first option is to continue following the emulator development path and start implementing the **store instructions**.

The second option is to temporarily focus on making the current emulator into a more presentable **version 0.5 / beta-style release**, such as creating a downloadable or easily runnable version that I could showcase on GitHub.

Having a more complete and usable version of the emulator could also be useful for my **resume and future internship interviews**, rather than only having the source code of an unfinished development project.

Alongside this decision, I also want to spend some time strengthening my understanding of some C++ concepts that have been confusing me during the development of the emulator.

In particular, I want to properly revise:

* **Pointers vs references**
* `*` vs `&`
* **Pass-by-value vs pass-by-reference**
* **Function declaration and definition**
* **Function prototypes**
* **Pointers to class members / member pointers**
* The terminology and differences between these concepts

I understand most of these concepts individually, but I want to make my understanding much stronger so that I am not simply using these features because they appear in the tutorial or existing code.

Therefore, the next session will involve both deciding the next development direction of the emulator and strengthening these fundamental C++ concepts.

### Sign-Off

**Time:** 3:05 AM
*Date:** 27 September 2026

# 30 October 2026

## What I Worked On

After almost a month since my last development log on 27 September, I finally sat down and continued working on my 6502 Microprocessor Emulator project.

October was quite hectic because of my birthday, examinations, file submissions, and other responsibilities. I also spent time applying for internships and part-time jobs, hoping to focus more on finding an opportunity. However, I did not get the response I was expecting, so I have decided to focus on improving the project further and making it more presentable.

Today, I completed the **sixth tutorial video** and finished writing the unit tests for all three store instructions: **STA, STX, and STY**.

## Code Cleanup and Test File Organization

I made some changes to improve the existing code. Since the addressing helper functions and other helper functions only need to read memory, I made their memory parameters constant wherever appropriate. This helps prevent accidental modifications to memory from functions that are only supposed to read it.

I also reorganized the unit test files. Previously, the load-register tests and other tests were kept together in one large file, which was becoming difficult to navigate.

I renamed the existing file to `6502LoadRegisterTest.cpp` and created a separate file named `6502StoreRegisterTest.cpp` for the store-register tests.

I plan to follow the same approach for future instruction groups. Keeping related tests in separate files should make the project easier to manage as it grows.

## Learning About Lambda Functions

While following the sixth tutorial video, I also encountered **lambda functions** in C++.

I studied their basic syntax, including the capture list and parameter list. My understanding is that lambda functions allow us to write small functions directly where they are needed, keeping related logic together without always having to create a separate named function.

I still need to understand their uses more deeply, but this gave me a good starting point.

I also continued revising C++ fundamentals, including pointers, references, pass-by-value, pass-by-reference, and pointers to class members. I understand these concepts better than before, although some parts are still confusing. I am continuing to learn them through practical examples while working on the emulator.

## Store Instruction Unit Tests

The main achievement of this session was completing the unit tests for the three store instructions:

- **STA — Store Accumulator**
- **STX — Store X Register**
- **STY — Store Y Register**

These instructions perform the reverse operation of the load instructions. While load instructions read data from memory into a CPU register, store instructions write the value of a CPU register into memory.

Since I had already implemented and tested the load instructions, I could reuse a similar testing approach for the store instructions and adapt it to their behaviour.

I created the required helper functions and organized the new tests in the separate store-register test file.

With this work completed, **the unit tests for STA, STX, and STY are now complete**. The next step is to implement their actual behaviour in the emulator and verify that everything works correctly.

## Tutorial Progress and Current Status

With this session, the sixth tutorial video is officially completed.

The current progress is:

```text
Load Instructions
├── LDA
├── LDX
└── LDY

Store Instruction Unit Tests
├── STA
├── STX
└── STY
```

The load instructions and their applicable tests were completed earlier. The store-instruction tests are now ready, but the actual store-instruction implementation remains the next task.

## Next Step

For the next session, I plan to watch the **seventh tutorial video** and make notes about the changes required to implement the store instructions.

I want to turn those notes into a checklist and then follow it while implementing the code myself. The tutorial should give me the direction, while I use my own understanding and problem-solving skills to complete the implementation rather than blindly copying the code.

After completing the store instructions, I want to shift my attention towards making the emulator more presentable.

My goal is to prepare an initial **version 0.5 or beta release**, potentially with a simple GUI and a downloadable Windows executable. I want recruiters and other developers to be able to download and try the emulator easily through GitHub instead of having to compile and run the source code themselves.

I will explore using AI tools to help with the GUI and packaging while making sure I understand how the application works.

This will be an important milestone for the project. Before adding many more instructions, I want to make the work I have already completed easier for others to see, run, and evaluate.

## Sign-Off

**Date:** 30 October 2026  
**Time:** 00:37 local time

**Tutorial Six completed. STA, STX, and STY unit tests completed.**

Signing off for now. The next session will focus on implementing the store instructions, followed by preparations for an initial beta release.