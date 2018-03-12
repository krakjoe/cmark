--TEST--
CommonMark\Node fetch Code
--FILE--
<?php
$md = <<<MD
some `code`
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

$para = $doc->getFirstChild();

$code = $para->getFirstChild()->getNext();

if ($para instanceof CommonMark\Node\Paragraph &&
    $code instanceof CommonMark\Node\Code) {
	echo "OK";
}
?>
--EXPECT--
OK
