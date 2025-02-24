// Fetch curriculum data
fetch('frontend/data/curriculum.json')
    .then(response => response.json())
    .then(data => {
        console.log(data); // Log the data to verify it's loaded
        generateLessonPath(data, 'Unit 1', 'Chapter 1'); // Generate lessons for Unit 1, Chapter 1
    })
    .catch(error => console.error('Error loading curriculum:', error));

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

// Function to generate lesson paths
function generateLessonPath(curriculum, unit, chapter) {
    const lessonContainer = document.querySelector('.lesson-path');
    lessonContainer.innerHTML = ''; // Clear existing lessons

    const lessons = curriculum[unit][chapter];
    lessons.forEach((lesson, index) => {
        const lessonRow = document.createElement('div');
        lessonRow.classList.add('lesson-row', index % 2 === 0 ? 'left' : 'right');

        const lessonCircle = document.createElement('div');
        lessonCircle.classList.add('lesson-circle');
        lessonCircle.setAttribute('data-lesson', lesson.lesson);
        lessonCircle.setAttribute('title', lesson.title);
        lessonCircle.innerText = '?';

        lessonRow.appendChild(lessonCircle);
        lessonContainer.appendChild(lessonRow);
    });

    // Add gift box at the end
    const giftBox = document.createElement('div');
    giftBox.classList.add('gift-box');
    giftBox.innerHTML = '<i class="fas fa-gift"></i>';
    lessonContainer.appendChild(giftBox);
}

// Handle Lesson Clicks
document.addEventListener('click', (event) => {
    if (event.target.classList.contains('lesson-circle')) {
        const lesson = event.target.getAttribute('data-lesson');
        const title = event.target.getAttribute('title');
        alert(`Starting Lesson ${lesson}: ${title}`);
        event.target.classList.add('completed');
        event.target.innerText = '✔';

        // Check if all lessons are completed
        const incompleteLessons = document.querySelectorAll('.lesson-circle:not(.completed)');
        if (incompleteLessons.length === 0) {
            stopClock(); // Stop the clock when all lessons are completed
        }
    }
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
