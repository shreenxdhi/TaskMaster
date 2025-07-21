<div align="center">

# 📋 TaskMaster C++

### *A Powerful Cross-Platform Task Management System*

[![C++](https://img.shields.io/badge/C++-17+-blue.svg?style=for-the-badge&logo=c%2B%2B)](https://en.cppreference.com/)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg?style=for-the-badge)](https://github.com/shreenxdhi/TaskMaster)
[![License](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](LICENSE)

*Streamline your productivity with this elegant command-line task manager built with C++.*

---

</div>

## 🌟 Features

<table>
<tr>
<td>

### 📝 **Task Management**
- ➕ Create tasks with descriptions
- 🏆 Set priority levels (1-5)
- 📅 Add optional due dates
- ✅ Mark tasks as complete
- ✏️ Edit existing tasks
- 🗑️ Delete unwanted tasks

</td>
<td>

### 🔧 **Advanced Features**
- 📊 Priority-based task sorting
- 📋 Separate pending/completed views
- 💾 Persistent JSON storage
- 🖥️ Cross-platform compatibility
- 🎨 Clean, intuitive interface
- ⚡ Lightning-fast performance

</td>
</tr>
</table>

## 🚀 Quick Start

### 📋 Prerequisites

Ensure you have a C++17 compatible compiler installed.

<details>
<summary><b>🪟 Windows</b></summary>
Install MinGW-w64 (via MSYS2 or standalone) or Visual Studio with the "Desktop development with C++" workload.
</details>

<details>
<summary><b>🍎 macOS</b></summary>

```bash
# Install Xcode Command Line Tools (includes clang)
xcode-select --install
```

</details>

<details>
<summary><b>🐧 Linux</b></summary>

```bash
# Ubuntu/Debian
sudo apt-get update && sudo apt-get install build-essential

# Fedora/CentOS
sudo dnf groupinstall "Development Tools"
```

</details>

### 🎯 Build & Run

#### Method 1: Using the Makefile (Recommended on macOS/Linux)
```bash
# Clone the repository
git clone [https://github.com/shreenxdhi/TaskMaster.git](https://github.com/shreenxdhi/TaskMaster.git)
cd TaskMaster

# Build the project
make

# Run the application
./taskmaster
```

#### Method 2: Manual Compilation
```bash
# On macOS/Linux
g++ -std=c++17 -o taskmaster task.cpp
./taskmaster

# On Windows (using MinGW)
g++ -std=c++17 -o taskmaster.exe task.cpp
taskmaster.exe
```

## 📱 Application Interface

```
Welcome to TaskMaster C++!
===========================
 [1] Add a new task
 [2] List pending tasks
 [3] Mark a task as complete
 [4] Edit a task
 [5] Delete a task
 [6] View completed tasks
 [7] Exit

Enter your choice: _
```

## 📁 Project Structure

```
📦 TaskMaster/
├── 📄 task.cpp          # Core application logic
├── 📄 Makefile          # Build instructions
├── 📖 README.md         # This documentation
└── 📜 LICENSE           # MIT License
```

## 🤝 Contributing

Contributions are welcome! Please fork the repository, make your changes, and open a pull request.

1.  **Fork** the repository.
2.  **Create** your feature branch (`git checkout -b feature/AmazingFeature`).
3.  **Commit** your changes (`git commit -m 'Add some AmazingFeature'`).
4.  **Push** to the branch (`git push origin feature/AmazingFeature`).
5.  **Open** a Pull Request.

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

<div align="center">

### ⭐ Star this repository if TaskMaster helps you stay organized!

**Made with ❤️ and C++ by Shreenidhi V**

[Report Bug](https://github.com/shreenxdhi/TaskMaster/issues) • [Request Feature](https://github.com/shreenxdhi/TaskMaster/issues)

</div>
