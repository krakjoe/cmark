--TEST--
CommonMark\Node\Media URL Errors
--FILE--
<?php
$link = new CommonMark\Node\Media\Link;

try {
	$link->setURL([]);
} catch(InvalidArgumentException $ex) {
	echo "OK\n";
}
?>
--EXPECT--
OK
