<?php


include ('User.php');

$User1 = new User();
$User1->setId(9);
$User1->setFirst_Name("Julien");
$User1->setLast_Name("Rihani");
$User1->setStage_Name("Jux");
$User1->setPicture_Link("EMPTY");
$User1->setBirthday("1992-01-09");
//$User1->select();
$User1->insert();
$User1->display();
//$User1->update();
//$User1->delete();

?>