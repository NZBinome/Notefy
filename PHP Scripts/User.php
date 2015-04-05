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
    var $columns;

    function __construct()
    {
      $this->Converter=new Converter("Users");
      $this->columns=$this->Converter->describe();
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
      $Keys = array($this->columns[0]);
      $Values = array($this->Id);
      $Results=$this->Converter->select($Keys,$Values);
      $i=0;
      while ($i<count($Results)) 
      {
        $this->First_Name=$Results[$i][$this->columns[1]];
        $this->Last_Name=$Results[$i][$this->columns[2]];
        $this->Stage_Name=$Results[$i][$this->columns[3]];
        $this->Picture_Link=$Results[$i][$this->columns[4]];
        $this->Birthday=$Results[$i][$this->columns[5]];
        $i=$i+1;
      }
    }

    function insert()
    {
      $i=0;
      while ($i<count($this->columns)-1) {
        $Keys[$i]=$this->columns[$i+1];
        $i=$i+1;
      }
      $Values = array("'$this->First_Name'","'$this->Last_Name'","'$this->Stage_Name'","'$this->Picture_Link'","'$this->Birthday'");
      $this->Id = $this->Converter->insert($Keys,$Values);
    }

    function update()
    {
      $i=0;
      while ($i<count($this->columns)-1) {
        $Keys[$i]=$this->columns[$i+1];
        $i=$i+1;
      }
      $Values = array("'$this->First_Name'","'$this->Last_Name'","'$this->Stage_Name'","'$this->Picture_Link'","'$this->Birthday'");
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
      echo "User <br/>";
      echo "Id : " . $this->Id . "<br/>";
      echo "Last_Name : " . $this->Last_Name . "<br/>";
      echo "First_Name : " . $this->First_Name . "<br/>";
      echo "Stage_Name : " . $this->Stage_Name . "<br/>";
      echo "Birthday : " . $this->Birthday . "<br/>";
      echo "Picture_Link : " . $this->Picture_Link . "<br/>";
    }

}
?>