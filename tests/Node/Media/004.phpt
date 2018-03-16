--TEST--
CommonMark\Node\IMedia URL
--FILE--
<?php
$link = new CommonMark\Node\Link;
$link->setURL("OK");

echo $link->getURL();
?>
--EXPECT--
OK
