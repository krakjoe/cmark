--TEST--
CommonMark\Node\IMedia Title
--FILE--
<?php
$link = new CommonMark\Node\Link;
$link->setTitle("OK");

echo $link->getTitle();
?>
--EXPECT--
OK
