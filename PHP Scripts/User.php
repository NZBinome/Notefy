<?php

include ('Converter.php');

class  User
{
    var $Id;
    var $Last_Name;
    var $First_Name;
    var $Stage_Name;
    var $Birthday;
    var $Picture_Link;
    var $Converter;

    function __construct()
    {
      $this->Converter=new Converter();
      $this->Converter->setTable("Users");
    }

    function setId($par)
    {
      $this->Id=$par;
    }

    function setFirst_Name($par)
    {
       $this->First_Name = $par;
    }

    function setLast_Name($par)
    {
       $this->Last_Name = $par;
    }

    function setStage_Name($par)
    {
       $this->Stage_Name = $par;
    }

    function setBirthday($par)
    {
      $this->Birthday=date("Y-m-d",strtotime($par));
    }

    function setPicture_Link($par)
    {
      $this->Picture_Link=$par;
    }

    function getId()
    {
      return $this->Id;
    }

    function getFirst_Name()
    {
       return $this->First_Name;
    }

    function getLast_Name()
    {
       return $this->Last_Name;
    }

    function getStage_Name()
    {
       return $this->Stage_Name;
    }

    function getBirthday()
    {
      return $this->Birthday;
    }

    function getPicture_Link()
    {
      return $this->Picture_Link;
    }

    function select()
    {
      $Keys = array("Id");
      $Values = array($this->Id);
      $Results=$this->Converter->select($Keys,$Values);
      $this->First_Name=$Results['First_Name'];
      $this->Last_Name=$Results['Last_Name'];
      $this->Stage_Name=$Results['Stage_Name'];
      $this->Birthday=$Results['Birthday'];
      $this->Picture_Link=$Results['Picture_Link'];
    }

    function insert()
    {
      $Keys = array("First_Name","Last_Name","Stage_Name","Picture_Link","Birthday");
      $Values = array("'$this->First_Name'","'$this->Last_Name'","'$this->Stage_Name'","'$this->Picture_Link'","'$this->Birthday'");
      $this->Id = $this->Converter->insert($Keys,$Values);
    }

    function update()
    {
      $Keys=array("Id","First_Name","Last_Name","Stage_Name","Picture_Link","Birthday");
      $Values = array("$this->Id","'$this->First_Name'","'$this->Last_Name'","'$this->Stage_Name'","'$this->Picture_Link'","'$this->Birthday'");
      $this->Converter->update($Keys,$Values);
    }

    function delete()
    {
      $Keys = array("Id");
      $Values = array($this->Id);
      $this->Converter->delete($Keys,$Values);
    }

    function display()
    {
      echo "Id : " . $this->Id . "<br/>";
      echo "Last_Name : " . $this->Last_Name . "<br/>";
      echo "First_Name : " . $this->First_Name . "<br/>";
      echo "Stage_Name : " . $this->Stage_Name . "<br/>";
      echo "Birthday : " . $this->Birthday . "<br/>";
      echo "Picture_Link : " . $this->Picture_Link . "<br/>";
    }

}
?>