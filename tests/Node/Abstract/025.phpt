--TEST--
CommonMark\Node appendChild used
--FILE--
<?php
$doc = new CommonMark\Node\Document;
$para = new CommonMark\Node\Paragraph;

$doc->appendChild($para);

try {
	$doc->appendChild($para);
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
