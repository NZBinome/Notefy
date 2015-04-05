<?php

include ('Converter.php');
class  Melody
{
	var $Id;
	var $File_Link;
	var $Title;
	var $Date;
	var $User_Id;
	var $Converter;
    var $columns;

	function __construct()
    {
    	$this->Converter=new Converter("Melodies");
        $this->columns=$this->Converter->describe();
    }

    function setId($par)
    {
    	$this->Id=$par;
    }

    function setFile_Link($par)
    {
    	$this->File_Link=$par;
    }

    function setTitle($par)
    {
    	$this->Title=$par;
    }

    function setDate($par)
    {
    	$this->Date=date("Y-m-d",strtotime($par));
    }

    function setUser_Id($par)
    {
    	$this->User_Id=$par;
    }

    function getId()
    {
    	return $this->Id;
    }

    function getFile_Link()
    {
    	return $this->File_Link;
    }

    function getTitle()
    {
    	return $this->Title;
    }

    function getDate()
    {
    	return $this->Date;
    }

    function getUser_Id($par)
    {
    	return $this->User_Id;
    }

    function select()
    {
    	$Keys = array($this->columns[0]);
    	$Values = array($this->Id);
    	$Results=$this->Converter->select($Keys,$Values);
        $i=0;
        while ($i<count($Results)) 
        {
    	   $this->File_Link=$Results[$i][$this->columns[1]];
    	   $this->Title=$Results[$i][$this->columns[2]];
    	   $this->Date=$Results[$i][$this->columns[3]];
    	   $this->User_Id=$Results[$i][$this->columns[4]];
           $i=$i+1;
        }
    }

    function insert()
    {
        $i=0;
        while ($i<count($this->columns)-1) 
        {
            $Keys[$i]=$this->columns[$i+1];
            $i=$i+1;
        }

      	$Values = array("'$this->File_Link'","'$this->Title'","'$this->Date'","'$this->User_Id'");
      	$this->Id = $this->Converter->insert($Keys,$Values);
    }

    function update()
    {
    	$i=0;
        while ($i<count($this->columns)-1) 
        {
            $Keys[$i]=$this->columns[$i+1];
            $i=$i+1;
        }
      	$Values = array("'$this->File_Link'","'$this->Title'","'$this->Date'","'$this->User_Id'");
        $ParaKeys=array($this->columns[0]);
        $ParaValues=array("$this->Id");
        $this->Converter->update($Keys,$Values,$ParaKeys,$ParaValues);
    }

    function delete()
    {
    	$Keys = array($this->columns[0]);
      	$Values = array($this->Id);
      	$this->Converter->delete($Keys,$Values);
    }

    function display()
    {
        echo "Melody <br/>";
    	echo "Id : " . $this->Id . "<br/>";
    	echo "File_Link : " . $this->File_Link . "<br/>";
    	echo "Title : " . $this->Title . "<br/>";
    	echo "Date : " . $this->Date . "<br/>";
    	echo "User_Id : " . $this->User_Id . "<br/>";
    }
}
?>