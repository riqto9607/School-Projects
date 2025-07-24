$(document).ready(function() {
    // Add click event listeners to all h2 elements with class "toggleSummary"
    $("h2.toggleSummary").click(function() {
        // Toggle the next summary element's visibility
        $(this).next(".summary").slideToggle(); // Use slideToggle to animate the display
        $(this).toggleClass("collapsed");
    });
});

