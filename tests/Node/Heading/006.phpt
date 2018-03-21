--TEST--
CommonMark\Node\Heading incorrect read
--FILE--
<?php
$heading = new CommonMark\Node\Heading();

try {
	$zero = 0;
	$heading->$zero;
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
