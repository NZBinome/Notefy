<?php

include 'Bridge.php';
include 'Share.php';

$UserId = $_GET['UserId'];
$MelodyId = $_GET['MelodyId'];

$Share1 = new Share($UserId,$MelodyId);
$Share1->delete();

?>