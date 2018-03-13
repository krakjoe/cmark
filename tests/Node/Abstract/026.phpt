--TEST--
CommonMark\Node prependChild used
--FILE--
<?php
$doc = new CommonMark\Node\Document;
$para = new CommonMark\Node\Paragraph;

$doc->appendChild($para);

try {
	$doc->prependChild($para);
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
