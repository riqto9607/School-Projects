# Server Management & Administration Project
**Universiti Tunku Abdul Rahman (UTAR) — UCCN3004**

## 👨‍💻 Course Info
- **Course:** UCCN3004 Server Management and Administration  
- **Lecturer:** Dr. Fityanul Akhyar  
- **Semester:** 2024/06  
- **Student Name:** Wong Pei Kei  
- **Student ID:** 2207466

---

## 🧩 Project Overview

This GitHub repository contains my submissions for two individual assignments under the Server Management course, focusing on the installation, configuration, and testing of various server tools on Ubuntu 20.04 LTS. The goal is to demonstrate hands-on knowledge of system administration, networking tools, and service deployment.

---

## 📝 Assignment 1: Hadoop as a Data Warehouse

### 🔧 Objective:
Install and configure Hadoop (pseudo-distributed mode) on Ubuntu to serve as a basic data warehouse system.

### 🚀 Key Tasks:
- Installed Java JDK and Hadoop on Ubuntu.
- Configured Hadoop `core-site.xml`, `hdfs-site.xml`, `mapred-site.xml`, and `yarn-site.xml`.
- Set up SSH for HDFS user.
- Successfully started HDFS and YARN services.
- Tested data warehouse setup with file upload and MapReduce operations.

---

## 🧪 Assignment 2: Mini Project – Proxy & Load Balancing Setup

### 🌐 Objective:
Configure and test Squid Proxy, NGINX Web Server, and HAProxy Load Balancer on Ubuntu server instances.

### 📦 Tools:
- **Squid Proxy:** Configured caching and ACLs.
- **NGINX:** Deployed as a web server serving static content.
- **HAProxy:** Load balanced requests to multiple NGINX servers.

### 🔧 Setup Summary:
- 3 Ubuntu VMs: Squid server, NGINX server(s), HAProxy balancer.
- Adjusted config files (`squid.conf`, `nginx.conf`, `haproxy.cfg`) to enable caching, reverse proxying, and balancing.
- Verified access control and performance with testing tools.
