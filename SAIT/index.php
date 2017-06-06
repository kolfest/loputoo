<!DOCTYPE html>
<html>
<head>
<style>
div {
    width: 960px;
    height: 250px;
}

div div {
    float: left;
    background-color: lightblue;
    position: relative;
    width: 300px;
    padding: 50px;
    border-style: solid;
    border-width: 5px;
    font-weight:bold;
    margin-bottom: 20px
    margin-right: 20px
}
</style>
</head>

<body>
<?php

$dbhost = '';
$dbuser = '';
$dbpass = '';
$dbname = '';
$count = 0;
$query="SELECT  * FROM ntw_map";

$conn = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);
$retval = mysqli_query($conn, $query);
$number_of_devices = mysqli_num_rows($retval);
$sql_addr_query = "SELECT device_addr FROM ntwk_map GROUP BY device_addr;";
$ntwk_map = send_query($sql_addr_query);

while($count<$number_of_devices)
{

    while($row1 = mysqli_fetch_array($ntwk_map))
    {
        $sql2 = "SELECT leaf_addr,timestamp,battery, temp, hum, rssi \n"
            . "FROM data2\n"
            . "WHERE timestamp = (SELECT MAX(timestamp) \n"
            . "FROM data2\n"
            . "WHERE leaf_addr = ({$row1['device_addr']})\n"
            . "GROUP BY leaf_addr";

        $retval = mysqli_query($conn,$sql2);

        	while($row2 = mysqli_fetch_array($retval))
        	{
        	   echo "<div />";
        	   echo "<div />";

        	   echo
        	    $row2['id'] . "Temp:" . $row2['temp'] . 
        	   " C<br><br>Hum: " . $row2['hum'] . 
        	   " %<br><br>Battery: " . $row2['battery']  . 
        	   " V<br><br>RSSI " . $row2['rssi']  . 
        	   " dBm<br><br>leaf_addr: " . $row2['leaf_addr']. 
        	   "<br><br>M66detud: " . $row2['timestamp'];

        	   echo "<br />";
        	   echo"</div />";
        	}
    }        
    $count++;
}
?>

</body>
</html>

