--TEST--
CommonMark\Node\IMedia URL
--FILE--
<?php
$link = new CommonMark\Node\Link;
$link->url = "OK";

echo $link->url;
?>
--EXPECT--
OK
