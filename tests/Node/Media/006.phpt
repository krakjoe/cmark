--TEST--
CommonMark\Node\Media URL Errors
--FILE--
<?php
$link = new CommonMark\Node\Media\Link;

if (!$link->getURL()) {
	echo "OK";
}
?>
--EXPECT--
OK
