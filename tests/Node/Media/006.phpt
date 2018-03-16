--TEST--
CommonMark\Node\IMedia URL Errors
--FILE--
<?php
$link = new CommonMark\Node\Link;

if (!$link->getURL()) {
	echo "OK";
}
?>
--EXPECT--
OK
