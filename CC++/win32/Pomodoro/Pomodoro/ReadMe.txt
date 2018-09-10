========================================================================
    WIN32 APPLICATION : Pomodoro Project Overview
========================================================================

- Developer: Đoàn Hiếu Tâm
- Student ID: 1412477
- Email: nhoxbypass@gmail.com

========================================================================

A pomodoro timer allow people to work and rest in a scientifical way.

	Youtube Link: https://www.youtube.com/watch?v=3f-3qH7QrwY

	Main flow:
Full fill Job name, set your goal and press START button, the timer will countdown the working time for you
After 45 mins work, you get a pomodoro, and you will take a short break for 5 minutes.
After 4 pomodoro taken, user can take a long break to work around for 20-25 minutes.
Users can stop timer whenever they want


	Additional flow:
- Enter "TEST", "a123", or "%#$^^" to Goal edit box, your character will not be recorded, and a warning message appear
- Enter number like -3, -5, 0, 1.5, 3.1416 to Goal edit box, you will receive a error message "Number of goal must greater than zero!"
- Leave the Goal, Job name edit box empty, you will receive a error message "Job name or number of goal must not be empty!"


	Changelog v1.0: Allow user to resize the main window, and the control will change position. When user exit application, the size of window
will be saved into initialization named "config.ini"
And when user run application again, the old size will be loaded