--TEST--
CommonMark\Node\IMedia Title
--FILE--
<?php
$link = new CommonMark\Node\Link;
$link->title = "OK";

echo $link->title;
?>
--EXPECT--
OK
