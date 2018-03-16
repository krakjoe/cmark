--TEST--
CommonMark\Node\IMedia Title Errors
--FILE--
<?php
$link = new CommonMark\Node\Link;

if (!$link->getTitle()) {
	echo "OK";
}
?>
--EXPECT--
OK
