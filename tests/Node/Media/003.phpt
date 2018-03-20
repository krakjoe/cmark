--TEST--
CommonMark\Node\IMedia Title Errors
--FILE--
<?php
$link = new CommonMark\Node\Link;

if (!$link->title) {
	echo "OK";
}
?>
--EXPECT--
OK
