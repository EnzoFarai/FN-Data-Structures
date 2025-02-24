
// Update Streak, Gems, and Hearts
   document.getElementById('streak').innerText = localStorage.getItem('streak') || 0;
   document.getElementById('gems').innerText = localStorage.getItem('gems') || 208;
   document.getElementById('hearts').innerText = localStorage.getItem('hearts') || 5;

   // Clock Variables
   let startTime = null;
   let timerInterval = null;

   // Function to update the clock
   function updateClock() {
       if (!startTime) return;

       const now = new Date();
       const elapsedTime = Math.floor((now - startTime) / 1000); // Time in seconds

       const hours = Math.floor(elapsedTime / 3600);
       const minutes = Math.floor((elapsedTime % 3600) / 60);
       const seconds = elapsedTime % 60;

       document.getElementById('hours').innerText = String(hours).padStart(2, '0');
       document.getElementById('minutes').innerText = String(minutes).padStart(2, '0');
       document.getElementById('seconds').innerText = String(seconds).padStart(2, '0');
   }

   // Function to start the clock
   function startClock() {
       if (!startTime) {
           startTime = new Date();
           timerInterval = setInterval(updateClock, 1000);
       }
   }

   // Function to stop the clock
   function stopClock() {
       clearInterval(timerInterval);
   }

   // Handle Lesson Clicks
   const lessonCircles = document.querySelectorAll('.lesson-circle');
   lessonCircles.forEach((circle, index) => {
       circle.addEventListener('click', () => {
           if (index === 0) {
               startClock(); // Start the clock when the first lesson is clicked
           }

           const lesson = circle.getAttribute('data-lesson');
           const title = circle.getAttribute('title');
           alert(`Starting Lesson ${lesson}: ${title}`);
           circle.classList.add('completed');
           circle.innerText = '✔';

           // Check if all lessons are completed
           const incompleteLessons = document.querySelectorAll('.lesson-circle:not(.completed)');
           if (incompleteLessons.length === 0) {
               stopClock(); // Stop the clock when all lessons are completed
           }
       });
   });

   // Handle Gift Box Click
   const giftBox = document.querySelector('.gift-box');
   giftBox.addEventListener('click', () => {
       if (!giftBox.classList.contains('gold')) {
           // Turn the gift box gold
           giftBox.classList.add('gold');

           // Increase gems by 100
           const gems = parseInt(localStorage.getItem('gems')) || 208;
           localStorage.setItem('gems', gems + 100);
           document.getElementById('gems').innerText = gems + 100;

           alert('You earned 100 gems!');
       }
   });
