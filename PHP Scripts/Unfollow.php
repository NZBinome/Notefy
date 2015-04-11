<?php

include 'Bridge.php';
include 'Follows.php';

$Followed = $_GET['Followed'];
$Follower = $_GET['Follower'];

$Follows1 = new Follows($Follower,$Followed);
$Follows1->delete();

?>