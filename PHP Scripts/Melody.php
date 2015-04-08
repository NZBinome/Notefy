<?php

class  Melody
{
	var $Id;
	var $File_Link;
	var $Title;
	var $Date;
	var $User_Id;
    var $Key_Id;
    var $Key_File_Link;
    var $Key_Title;
    var $Key_Date;
    var $Key_User_Id;
	var $Converter;

    function __construct() 
    { 
        $a = func_get_args(); 
        $i = func_num_args(); 
        if (method_exists($this,$f='__construct'.$i)) { 
            call_user_func_array(array($this,$f),$a); 
        } 
    }

    function __construct1($Id)
    {
      $this->__construct0();
      $this->Id=$Id;
      $this->select();
    }

    function __construct0()
    {
      $this->Converter=new Bridge("Melodies");
      $this->setKeys();
    }

    function setKeys()
    {
        $this->Key_Id=$this->Converter->Attributes[0];
        $this->Key_File_Link=$this->Converter->Attributes[1];
        $this->Key_Title=$this->Converter->Attributes[2];
        $this->Key_Date=$this->Converter->Attributes[3];
        $this->Key_User_Id=$this->Converter->Attributes[4];
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

    function setMelody($Result)
    {
        $this->Id=$Result[$this->Key_Id];
        $this->File_Link=$Result[$this->Key_File_Link];
        $this->Title=$Result[$this->Key_Title];
        $this->Date=$Result[$this->Key_Date];
        $this->User_Id=$Result[$this->Key_User_Id]; 
    }

    function select()
    {
    	$Keys = array($this->Key_Id);
    	$Values = array($this->Id);
    	$Results=$this->Converter->select($Keys,$Values);
        $i=0;
        while ($i<count($Results)) 
        {
    	   $this->setMelody($Results[$i]);
           $i=$i+1;
        }
    }

    function setParameters(){
        $Keys[0]=$this->Key_File_Link;
        $Keys[1]=$this->Key_Title;
        $Keys[2]=$this->Key_Date;
        $Keys[3]=$this->Key_User_Id;
        return $Keys;
    }

    function insert()
    {
      	$Values = array("'$this->File_Link'","'$this->Title'","'$this->Date'","'$this->User_Id'");
      	$this->Id = $this->Converter->insert($this->setParameters(),$Values);
    }

    function update()
    {
      	$Values = array("'$this->File_Link'","'$this->Title'","'$this->Date'","'$this->User_Id'");
        $ParaKeys=array($this->Key_Id);
        $ParaValues=array("$this->Id");
        $this->Converter->update($this->setParameters(),$Values,$ParaKeys,$ParaValues);
    }

    function delete()
    {
    	$Keys = array($this->Key_Id);
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