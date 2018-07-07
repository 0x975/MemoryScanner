# Task-Widget
Simple QT5 widget for enumiration all running processes in Linux operation system. QT5 process viewer, task widget

<h1> Feautures  </h1>
<ul>
  <li>Selection of one process</li>
  <li>Filtering table by regex in selected header</li>
  <li>Sorting table by headers</li>
  <li>Show main info about all running processes in a table</li>
</ul>

<h1> To do  </h1>
<ul>
  <li>add QTimer to get current state of running processes</li>
</ul>

<h1> Screenshot  </h1>
<img src="https://github.com/PavelMacarenko/Task-Widget/blob/master/screenshot.png">

<h1> Example of usage  </h1>
<p> Just clone this repository and add "TaskWidget" folder to your project. After that include widget, create new instance of <code> TaskWidget </code> and add it to some qlayout </p>
<pre><code> #include "TaskWidget/taskwidget.h"
 TaskWidget *taskWidget; 
 taskWidget = new TaskWidget(); 
 taskWidget->setFilterVisable(true); 
</code></pre>
