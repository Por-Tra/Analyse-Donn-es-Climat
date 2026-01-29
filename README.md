# Climate Data Analysis

<div align="center">

[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](https://cplusplus.com/)

A professional-grade C++ application for analyzing and visualizing meteorological data with interactive graphical representations.

[Features](#-features) • [Getting Started](#-getting-started) • [Usage](#-usage) • [Architecture](#-architecture)

</div>

---

## 📋 Overview

Climate Data Analysis is a first-year computer science project that provides a comprehensive solution for processing, analyzing, and visualizing meteorological datasets. Built with C++ and leveraging the LibGraph2 library, this application offers multiple data processing modes and dynamic graph visualization capabilities.

The application processes historical climate data from the Aigoual station and presents it through various analytical perspectives, from raw data to seasonal trends and tendencies.

---

## ✨ Features

### Data Processing
- **Raw Data Handling** - Direct access to original meteorological records
- **Temporal Aggregation** - Annual and decennial averages
- **Seasonal Analysis** - Seasonal trend computation and comparison
- **Statistical Functions** - Min/Max detection, temperature-based searches

### Visualization Modes
- **Bar Charts** - Clear representation of quantitative data
- **Scatter Plots** - Individual data point visualization
- **Line Graphs** - Trend visualization and data continuity
- **Trend Curves** - Automatic tendencies analysis with mathematical modeling

### Interactive Interface
- Real-time graph switching
- Multiple data aggregation modes
- Background audio integration
- Full Windows GUI with responsive rendering

---

## 🛠️ Tech Stack

- **Language**: C++17
- **Graphics**: LibGraph2 (custom visualization library)
- **Platform**: Windows (x64 architecture)
- **Build System**: Visual Studio (MSVC)
- **Data Format**: CSV (Aigoual meteorological dataset)

---

## 🚀 Getting Started

### Prerequisites
- Visual Studio 2019 or later
- Windows x64 environment
- C++ development tools (MSVC compiler)

### Installation

1. **Clone the repository**
```bash
git clone https://github.com/yourusername/Analyse-Donnees-Climat.git
cd Analyse-Donnees-Climat
```

2. **Open the solution**
```
Double-click TP13.sln to open in Visual Studio
```

3. **Build the project**
- Select Release or Debug configuration
- Build Solution (Ctrl+Shift+B)

4. **Run the application**
- Press F5 or navigate to x64/Release/TP13.exe

---

## 📖 Usage

### Data Processing Modes

#### Raw Data
View unprocessed meteorological measurements directly from the CSV dataset.

#### Annual Average
Compute mean values for each year in the dataset for trend identification.

#### Decennial Average
Group data by 10-year intervals to identify longer-term patterns.

#### Seasonal Average
Analyze seasonal variations (spring, summer, autumn, winter) throughout the dataset.

### Graph Types

Select between different visualization styles:
- **Bars**: Comparative analysis of discrete values
- **Points**: Individual measurement visualization
- **Points + Lines**: Combined discrete and continuous views
- **Trend Curve**: Statistical regression and tendency visualization

---

## 📁 Project Structure

```
Analyse-Donnees-Climat/
├── TP13/
│   ├── main.cpp              # Application entry point and GUI management
│   ├── CData.cpp/h           # Data processing and analysis engine
│   ├── CPoint.h              # Point structure definition
│   ├── SData.h               # Data structure definition
│   ├── prog.cpp              # Auxiliary functionality
│   ├── aigoual_Mensuel.csv   # Meteorological dataset
│   ├── inc/
│   │   └── LibGraph2.h       # Graphics library header
│   └── lib/
│       └── x64/              # Compiled libraries
├── TP13.sln                  # Visual Studio solution file
└── README.md                 # This file
```

---

## 🔧 Core Classes

### CData
Handles all data processing and statistical computations:
- `MoyenneParAnnee()` - Annual average calculation
- `MoyenneToutLes10ans()` - Decennial average calculation
- `MoyenneParSaison()` - Seasonal average calculation
- `RechercheDateTemperature()` - Temperature-based data search
- `courbeDeTendance()` - Trend curve computation

### Data Structures
- **Donnee** - Individual meteorological record
- **CPoint** - Graphical coordinate representation

---

## 📊 Dataset

The application processes the **Aigoual Monthly Dataset** (`aigoual_Mensuel.csv`), containing:
- Historical temperature measurements
- Monthly aggregated meteorological data
- Multi-decade time span for trend analysis

---

## 🎯 Key Functionalities

- ✅ Multi-format data import from CSV files
- ✅ Real-time graph generation and rendering
- ✅ Interactive mode switching without restart
- ✅ Statistical analysis algorithms
- ✅ Trend prediction and visualization
- ✅ User-friendly Windows interface


<div align="center">

**[⬆ back to top](#climate-data-analysis)**

</div>
