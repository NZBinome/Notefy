<?php 

include 'User.php';
include 'Bridge.php';
include 'Toolkit.php';
include 'Follows.php';

$Stage_Name= $_GET['StageName'];
$User1 = new User();
$User1->selectByStageName('"' . $Stage_Name . '"');
$ToSend = "<Root>";
$ToSend = $ToSend . "<SearchResult>" . $User1->getId() . "</SearchResult>";
$ToSend = $ToSend . "</Root>";

echo $ToSend;

?>