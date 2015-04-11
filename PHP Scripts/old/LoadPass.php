<?php

$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

 $result=mysqli_query($con,"SELECT IdVol,File FROM Vol WHERE (EtatVol='Actif' OR EtatVol='Arrive' Or EtatVol='Retarde') AND File IS NOT NULL");
 while ($row=mysqli_fetch_array($result)) {
  $Vol=$row['IdVol'];
  $File=$row['File'];

  //	$Vol='3';
$xml=simplexml_load_file($File);

		if($xml->Configuration[0]['nouveau']=="2"){
			////////////////
			  $sql="INSERT INTO EquipA () VALUES ()";
        if (!mysqli_query($con,$sql)){
        die('Error: ' . mysqli_error($con));
    }
    $entier=mysqli_query($con,"SELECT IdEq FROM EquipA WHERE IdEq=(SELECT max(IdEq) FROM EquipA)");
	while ($rang=mysqli_fetch_array($entier)) {
  	$a=$rang['IdEq'];
	}
	 //////////////
	$Com=$xml->Configuration[0]['compagnie'];
	$entier2=mysqli_query($con,"SELECT IdComp FROM Compagnie WHERE NomComp='$Com'");
	while ($rang2=mysqli_fetch_array($entier2)) {
  	$Comp=$rang2['IdComp'];
	}
	
	/////////////////////
		$entier=mysqli_query($con,"SELECT IdEDL FROM EDL WHERE IdEDL=(SELECT max(IdEDL) FROM EDL)");
		while ($rang=mysqli_fetch_array($entier)) {
  		$NID=$rang['IdEDL'];
		}
		
		////////////////////        
		$arr=array();
			foreach ($xml->Employe as $Emp):
        $NE=$Emp->Nom;
        $PE=$Emp->Prenom;
        $PEm=$Emp->Poste;
        $CE=$Emp->Connu;
        if($CE=="1"){
        	$result=mysqli_query($con,"SELECT IdEDL FROM EDL WHERE NomEDL=$NE AND PrenomEDL=$PE AND Poste=$PEm");
			while ($rang=mysqli_fetch_array($result)) {
  			array_push($arr,$rang['IdEDL']);
  			//echo $rang['IdEDL'];
}
        }
        if($CE=="0"){
        	$NID=$NID+1;
        	 $sql="INSERT INTO EDL (IdComp,NomEDL,PrenomEDL,Poste) VALUES ($Comp,'$NE','$PE','$PEm')";
        if (!mysqli_query($con,$sql)){
        die('Error: ' . mysqli_error($con));
    }
    array_push($arr,$NID);
        }
        endforeach;
        //////////////////

        $i=0;
        while($i<count($arr)){
        	echo count($arr);
        	//echo current($arr);
        	$val=current($arr);
        	//echo $val;
        	$sql="INSERT INTO forme2 (IdEq,IdEDL) VALUES ($a,$val)";
        if (!mysqli_query($con,$sql)){
        die('Error: ' . mysqli_error($con));
    }
    $i=$i+1;
    next($arr);
        }
        $sql="UPDATE Vol SET IdEq=$a WHERE IdVol=$Vol";
        if (!mysqli_query($con,$sql)){
        die('Error: ' . mysqli_error($con));
    }
     //   
	}
	

	if($xml->Configuration[0]['nouveau']=="1"){

		$Prog=$xml->Configuration[0]['Prog'];
		$Date=$xml->Configuration[0]['Date'];
		$Heure=$xml->Configuration[0]['Heure'];
 //   echo $Date . "<br>";
   // echo $Prog . "<br>";
    //echo $Heure . "<br>";
		$result=mysqli_query($con,"SELECT IdEq FROM Vol WHERE Code='$Prog' AND DatPreVol='$Date' AND HeurPreVol='$Heure'");
while ($rang=mysqli_fetch_array($result)) {
  $Eq=$rang['IdEq'];
}
  echo $Eq ."<br>" ;
//echo $Eq;
       $sql="UPDATE Vol SET IdEq=$Eq WHERE IdVol=$Vol";
        if (!mysqli_query($con,$sql)){
        die('Error: ' . mysqli_error($con));
    }
	}
	
  foreach ($xml->Passager as $pass):
        $NP=$pass->Nom;
        $PP=$pass->Prenom;
        $NPa=$pass->NumPass;
        $sql="INSERT INTO Passager (IdVol,NomPass, NumPass,PrenomPass) VALUES ($Vol,'$NP','$NPa','$PP')";
        if (!mysqli_query($con,$sql)){
        die('Error: ' . mysqli_error($con));
    }
        endforeach;


     $sql="UPDATE Vol SET File=NULL WHERE IdVol=$Vol";
        if (!mysqli_query($con,$sql)){
        die('Error: ' . mysqli_error($con));
    }

     }
      
mysqli_close($con);
      ?>