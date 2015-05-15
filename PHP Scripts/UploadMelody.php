<?php

$myparam = $_FILES['userfile'];
$UserId = $_POST['UserId'];
$MelodyName= $_POST['MelodyName'];
$target_path = "Melodies/" . $UserId . "/" . $MelodyName . "/";


if (!file_exists("Melodies/" . $UserId)) 
{
	mkdir("Melodies/" . $UserId, 0777, true);
}

if (!file_exists("Melodies/" . $UserId . "/" . $MelodyName)) 
{
	mkdir("Melodies/" . $UserId . "/" . $MelodyName, 0777, true);
}

if(move_uploaded_file($myparam['tmp_name'], $target_path . basename( $myparam['name'])))
{ 
    echo "The file ". basename( $myparam['name']). " has been uploaded";
}

else 
{ 
	echo "There was an error uploading the file, please try again!"; 
} 


?>