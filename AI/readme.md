# Cardiovascular Risk Prediction Using Machine Learning

## Overview
This project focuses on developing machine learning models to predict cardiovascular risk levels (low, medium, high) using a dataset containing demographic, lifestyle, and health-related features. The goal is to explore the effectiveness of various algorithms in identifying risk factors and improving early detection of cardiovascular diseases.

---

## Dataset Description
The dataset consists of **2100 samples** with the following features:
- **Numerical Features (8):** Age, height (cm), weight (kg), vegetable servings per day, meals per day, water intake (L), exercise frequency, and income.
- **Categorical Features (10):** Gender, family history of cardiovascular disease, alcohol consumption, junk food intake, snacking habits, smoking status, transportation mode, TV watching frequency, discipline, and cardiovascular risk level (target variable).

Key observations:
- No missing values.
- Balanced representation of numerical and categorical data.
- Target variable (`cardiovascular_risk`) has three classes: low, medium, and high.

---

## Methodology

### 1. Data Exploration and Visualization
- **Summary Statistics:** Analyzed central tendencies and distributions of numerical features.
- **Visualizations:**  
  - Histograms for numerical feature distributions.
  - Box plots to compare age distributions across risk levels.
  - Heatmaps to identify correlations between features.
  - Bar charts to explore relationships (e.g., smoking vs. risk level).

### 2. Data Preprocessing
- **Train-Test Split:** 80% training, 20% testing.
- **Feature Scaling:** Standardized numerical features using `StandardScaler`.
- **Categorical Encoding:** Applied one-hot encoding to categorical features.
- **Class Imbalance Handling:** Used SMOTE (Synthetic Minority Over-sampling Technique) to balance the dataset.

### 3. Model Selection and Training
Four models were evaluated:
1. **K-Nearest Neighbors (KNN):** Simple, distance-based classifier.
2. **Support Vector Classifier (SVC):** Effective for high-dimensional data.
3. **Logistic Regression:** Baseline model for interpretability.
4. **Random Forest:** Ensemble method for robust performance.

### 4. Hyperparameter Tuning
- **Grid Search:** Optimized parameters (e.g., `n_neighbors` for KNN, `C` and `kernel` for SVC).
- **Cross-Validation:** 5-fold CV to ensure model generalizability.

### 5. Evaluation Metrics
- Accuracy, precision, recall, F1-score.
- Confusion matrices, ROC curves, and precision-recall curves.

---

## Results

### Performance Before SMOTE
- **KNN:** Accuracy = 83.51%, Recall = 80.38%.
- **SVC:** Accuracy = 94.88%, Recall = 94.23%.
- **Logistic Regression:** Accuracy = 97.26%, Recall = 96.74%.
- **Random Forest:** Accuracy = 95.65%, Recall = 95.01%.

### Performance After SMOTE
- **KNN:** Accuracy = 90.91%, Recall = 90.91%.
- **SVC:** Accuracy = 97.40%, Recall = 97.40%.
- **Logistic Regression:** Accuracy = 98.17%, Recall = 98.16%.
- **Random Forest:** Accuracy = 97.40%, Recall = 97.40%.

### Key Findings
- **Random Forest** achieved the highest AUC scores (PR AUC = 0.9961, ROC AUC = 0.9979) after SMOTE.
- **Feature Importance:** Alcohol consumption (`Alcohol_high`) and family history (`Family_history_yes`) were the top predictors.
- SMOTE significantly improved minority class prediction (e.g., recall for "low" and "medium" risk classes increased by ~10-15%).

---

## Strengths and Weaknesses of Models

| Model               | Strengths                                  | Weaknesses                                  |
|---------------------|-------------------------------------------|--------------------------------------------|
| **KNN**             | Simple, no training phase, flexible.      | Slow predictions, sensitive to noise.      |
| **SVC**             | Handles high dimensions, prevents overfitting. | Computationally heavy, hard to tune.      |
| **Logistic Regression** | Interpretable, fast, provides probabilities. | Assumes linearity, struggles with interactions. |
| **Random Forest**   | Robust, versatile, shows feature importance. | Computationally demanding, less interpretable. |

---

## Conclusion
- **Best Model:** Random Forest, due to its balance of accuracy and robustness.
- **Critical Features:** Alcohol consumption and family history are the most influential predictors.
- **Future Work:** Incorporate more data, explore deep learning models, and validate in clinical settings.
