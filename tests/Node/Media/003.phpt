--TEST--
CommonMark\Node\Media Title Errors
--FILE--
<?php
$link = new CommonMark\Node\Media\Link;

if (!$link->getTitle()) {
	echo "OK";
}
?>
--EXPECT--
OK
