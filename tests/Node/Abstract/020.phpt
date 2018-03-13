--TEST--
CommonMark\Node replace used
--FILE--
<?php
$doc = new CommonMark\Node\Document;
$para = new CommonMark\Node\Paragraph;

$doc->appendChild($para);

try {
	$para->replace($para);
} catch (RuntimeException $ex) {
	echo "OK";
}

?>
--EXPECT--
OK
