<?php

include 'Bridge.php';
include 'Comment.php';

$UserId = $_GET['UserId'];
$MelodyId = $_GET['MelodyId'];
$ScriptText = $_GET['Script'];

$Comment1 = new Comment();
$Comment1->setWriter($UserId);
$Comment1->setMelody($MelodyId);
date_default_timezone_set("Asia/Beirut");
$Comment1->setDate(date("Y-m-d H:i:s"));
$Comment1->setScript($ScriptText);
$Comment1->insert();
?>