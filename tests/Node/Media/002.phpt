--TEST--
CommonMark\Node\Media Title Errors
--FILE--
<?php
$link = new CommonMark\Node\Media\Link;

try {
	$link->setTitle([]);
} catch(InvalidArgumentException $ex) {
	echo "OK\n";
}
?>
--EXPECT--
OK
