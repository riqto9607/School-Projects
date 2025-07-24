const wrapper = document.querySelector('.wrapper');
const loginLink = document.querySelector('.login-link');
const registerLink = document.querySelector('.register-link');
const btnPopup = document.querySelector('.btnlogin-popup');
const iconClose = document.querySelector('.icon-close');
let dialogIsOpen = false;

registerLink.addEventListener('click', () => {
    wrapper.classList.add('active');
    const dialogOverlay = document.getElementById("dialogOverlay");
    const dialogBox = document.getElementById("dialogBox");
    dialogOverlay.style.display = "block";
    dialogBox.style.display = "block";
    dialogIsOpen = true; 
});

loginLink.addEventListener('click', () => {
    wrapper.classList.remove('active');
    dialogIsOpen = false;
});

btnPopup.addEventListener('click', () => {
    wrapper.classList.add('active-popup');
    dialogIsOpen = false;
});

iconClose.addEventListener('click', () => {
    wrapper.classList.remove('active-popup');
    dialogIsOpen = false;
});

document.addEventListener("DOMContentLoaded", function () {
    const openDialogButton = document.getElementById("openDialog");
    const dialogOverlay = document.getElementById("dialogOverlay");
    const dialogBox = document.getElementById("dialogBox");
    const closeDialog = document.getElementById("closeDialog");

    openDialogButton.addEventListener("click", function () {
        dialogOverlay.style.display = "block";
        dialogBox.style.display = "block";
        dialogIsOpen = true;
    });


    closeDialog.addEventListener("click", function () {
        dialogOverlay.style.display = "none";
        dialogBox.style.display = "none";
        dialogIsOpen = false;
    });
});

function setCookie(name, value, days) {
    var expires = "";
    if (days) {
        var date = new Date();
        date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
        expires = "; expires=" + date.toUTCString();
    }
    document.cookie = name + "=" + value + expires + "; path=/";
}

function getCookie(name) {
    var nameEQ = name + "=";
    var cookies = document.cookie.split(';');
    for (var i = 0; i < cookies.length; i++) {
        var cookie = cookies[i];
        while (cookie.charAt(0) == ' ') {
            cookie = cookie.substring(1, cookie.length);
        }
        if (cookie.indexOf(nameEQ) == 0) {
            return cookie.substring(nameEQ.length, cookie.length);
        }
    }
    return null;
}

document.querySelector('.login form').addEventListener('submit', function (event) {
    event.preventDefault(); 
    var email = document.querySelector('.login input[type="email"]').value;
    var password = document.querySelector('.login input[type="password"]').value;
    setCookie('login_email', email, 30); 
    setCookie('login_password', password, 30); 
});


document.querySelector('.register form').addEventListener('submit', function (event) {
    event.preventDefault(); 
    var username = document.querySelector('.register input[type="text"]').value;
    var email = document.querySelector('.register input[type="email"]').value;
    var password = document.querySelector('.register input[type="password"]').value;
    setCookie('register_username', username, 30); 
    setCookie('register_email', email, 30); 
    setCookie('register_password', password, 30); 
});

var savedLoginEmail = getCookie('login_email');
var savedLoginPassword = getCookie('login_password');
if (savedLoginEmail) {
    document.querySelector('.login input[type="email"]').value = savedLoginEmail;
}
if (savedLoginPassword) {
    document.querySelector('.login input[type="password"]').value = savedLoginPassword;
}

var savedRegisterUsername = getCookie('register_username');
var savedRegisterEmail = getCookie('register_email');
var savedRegisterPassword = getCookie('register_password');

if (savedRegisterUsername) {
    document.querySelector('.register input[type="text"]').value = savedRegisterUsername;
}
if (savedRegisterEmail) {
    document.querySelector('.register input[type="email"]').value = savedRegisterEmail;
}
if (savedRegisterPassword) {
    document.querySelector('.register input[type="password"]').value = savedRegisterPassword;
}

document.querySelector('.register form').addEventListener('submit', function (event) {
    event.preventDefault(); 

    const username = document.querySelector('.register input[type="text"]').value;
    const email = document.querySelector('.register input[type="email"]').value;
    const password = document.querySelector('.register input[type="password"]').value;
    const agreeCheckbox = document.querySelector('#agreeCheckbox');

    if (username && email && password && agreeCheckbox.checked) {
        setCookie('register_username', username, 30);
        setCookie('register_email', email, 30);
        setCookie('register_password', password, 30);
        
        openPopup();
    } else {
        alert('Please fill in all the required fields and agree to the terms and conditions.');
    }
});

function isUserRegistered(email, password) {
    var savedRegisterEmail = getCookie('register_email');
    var savedRegisterPassword = getCookie('register_password');
    
    if (email === savedRegisterEmail && password === savedRegisterPassword) {
        return true; 
    } else {
        return false; 
    }
}


document.querySelector('.login form').addEventListener('submit', function (event) {
    event.preventDefault(); 

    var email = document.querySelector('.login input[type="email"]').value;
    var password = document.querySelector('.login input[type="password"]').value;
    
    if (isUserRegistered(email, password)) {
        window.location.href = "mainpage.html";
    } else {
        alert('Invalid credentials. Please check your email and password.');
    }
});