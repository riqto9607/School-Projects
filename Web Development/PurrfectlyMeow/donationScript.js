function retrieveUserData() {

    if (localStorage.getItem("userData")) {

        let userData = JSON.parse(localStorage.getItem("userData"));
  

        console.log("Full Name: " + userData.fullName);
        console.log("Email: " + userData.email);
        console.log("Phone: " + userData.phone);
        console.log("Date of Birth (DD/MM/YYYY): " + userData.dobDD + "/" + userData.dobMM + "/" + userData.dobYYYY);
        console.log("Gender: " + userData.gender);
        console.log("Payment Method: " + userData.paymentMethod);
        console.log("Donation Amount: " + userData.donationAmount);

    } else {
        console.log("No user data found in local storage.");
    }
}

retrieveUserData();